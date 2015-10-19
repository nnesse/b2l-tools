#include "math3d.h"

#include <math.h>
#include <memory.h>

void math3d_mat4_mul(const struct math3d_mat4 *m1, const struct math3d_mat4 *m2, struct math3d_mat4 *m3)
{
	int i, j, k;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			float v = 0;
			for (k = 0; k < 4; k++) {
				v += m1->v[k][j] * m2->v[i][k];
			}
			m3->v[i][j] = v;
		}
	}
}

void math3d_mat4_zero(struct math3d_mat4 *m)
{
	memset(m, 0, sizeof(*m));
}

void math3d_mat4_identity(struct math3d_mat4 *m)
{
	math3d_mat4_zero(m);
	m->v[0][0] = 1;
	m->v[1][1] = 1;
	m->v[2][2] = 1;
	m->v[3][3] = 1;
}

void math3d_mat4_perspective(float fovy, float width, float height, float z_near, float z_far, struct math3d_mat4 *m)
{
	float f = 1.0/tan((fovy*M_PI)/2);
	float aspect = width / height;
	math3d_mat4_zero(m);
	m->v[0][0] = f/aspect;
	m->v[1][1] = f;
	m->v[2][2] = (z_far + z_near) / (z_near - z_far);
	m->v[2][3] = -1;
	m->v[3][2] = (2 * z_far * z_near) / (z_near - z_far);
}

float math3d_vec3_dot(const struct math3d_vec3 *v1, const struct math3d_vec3 *v2)
{
	return (v1->v[0] * v1->v[0] + v1->v[1] * v2->v[1] + v1->v[2] * v2->v[2]);
}

float math3d_vec3_length(const struct math3d_vec3 *v)
{
	return sqrtf(math3d_vec3_dot(v,v));
}

void math3d_vec3_cross(struct math3d_vec3 *a, struct math3d_vec3 *b, struct math3d_vec3 *c)
{
	c->v[0] = a->v[1] * b->v[2] - a->v[2] * b->v[1];
	c->v[1] = -a->v[0] * b->v[2] + a->v[2] * b->v[0];
	c->v[2] = a->v[0] * b->v[1] - a->v[1] * b->v[0];
}

void math3d_vec3_lerp(const struct math3d_vec3 *v1, const struct math3d_vec3 *v2, float d, struct math3d_vec3 *v3)
{
	int i;
	for (i = 0; i < 3; i++) {
		v3->v[i] = v1->v[i] * (1-d) + v2->v[i] * d;
	}
}

void math3d_vec3_normalize(struct math3d_vec3 *v)
{
	int i;
	float length = math3d_vec3_length(v);
	if (length > 0) {
		for (i = 0; i < 3; i++) {
			v->v[i] *= 1.0/length;
		}
	}
}

void math3d_spherical_lerp(const struct math3d_vec3 *v1_, const struct math3d_vec3 *v2_, float d, struct math3d_vec3 *v3)
{
	struct math3d_vec3 v1xv2;
	struct math3d_vec3 temp;
	struct math3d_vec3 v1;
       	struct math3d_vec3 v2;
	int i;
	for (i = 0; i < 3; i++) {
		v1.v[i] = v1_->v[i];
		v2.v[i] = v2_->v[i];
	}

	float v1_norm = math3d_vec3_length(&v1);
	float v2_norm = math3d_vec3_length(&v2);
	math3d_vec3_normalize(&v1);
	math3d_vec3_normalize(&v2);

	math3d_vec3_cross(&v1, &v2, &v1xv2);

	double theta;

	float dot = math3d_vec3_dot(&v1, &v2);
	if (dot > 1) dot = 1;
	theta = acosf(dot);

	if (theta < 0.05) {
		math3d_vec3_lerp(&v1, &v2, d, v3);
		return;
	}

	double phi = d * theta;

	math3d_vec3_normalize(&v1xv2);
	math3d_vec3_cross(&v1xv2, &v1, &temp);

	float cos_phi = cos(phi);
	float sin_phi = sin(phi);
	for (i = 0; i < 3; i++) {
		v3->v[i] = (cos_phi * v1.v[i] + sin_phi * temp.v[i]) * (v1_norm * (1-d) + v2_norm * d);
	}
}

void math3d_mat4_transpose(const struct math3d_mat4 *m, struct math3d_mat4 *m_t)
{
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			m_t->v[i][j] = m->v[j][i];
		}
	}
}

void math3d_mat4_mul_vec4(const struct math3d_mat4 *m, const struct math3d_vec4 *v1, struct math3d_vec4 *v2)
{
	int i, j;
	for (i = 0; i < 4; i++) {
		v2->v[i] = 0;
		for (j = 0; j < 4; j++) {
			v2->v[i] += m->v[j][i] * v1->v[j];
		}
	}
}

void math3d_mat3_mul_vec3(const struct math3d_mat3 *m, const struct math3d_vec3 *v1, struct math3d_vec3 *v2)
{
	int i, j;
	for (i = 0; i < 3; i++) {
		v2->v[i] = 0;
		for (j = 0; j < 3; j++) {
			v2->v[i] += m->v[j][i] * v1->v[j];
		}
	}
}

void math3d_quaternion_from_axis_angle(struct math3d_quaternion *q, const struct math3d_vec3 *axis, float angle)
{
	q->x = axis->v[0] * sin(angle/2);
	q->y = axis->v[1] * sin(angle/2);
	q->z = axis->v[2] * sin(angle/2);
	q->w = cos(angle/2);
}

void math3d_quaternion_to_mat3(const struct math3d_quaternion *q, struct math3d_mat3 *m)
{
	m->v[0][0] = 1 - (2 * q->y * q->y)- (2 * q->z * q->z);
	m->v[0][1] = (2 * q->x * q->y) + (2 * q->z * q->w);
	m->v[0][2] = (2 * q->x * q->z) - (2 * q->y * q->w);

	m->v[1][0] = (2 * q->x * q->y) - (2 * q->z * q->w);
	m->v[1][1] = 1 - (2 * q->x * q->x)- (2 * q->z * q->z);
	m->v[1][2] = (2 * q->y * q->z) + (2 * q->x * q->w);

	m->v[2][0] = (2 * q->x * q->z) + (2 * q->y * q->w);
	m->v[2][1] = (2 * q->y * q->z) - (2 * q->x * q->w);
	m->v[2][2] = 1 - (2 * q->x * q->x) - (2 * q->y * q->y);
}

void math3d_quaternion_to_mat4(const struct math3d_quaternion *q, struct math3d_mat4 *m)
{
	struct math3d_mat3 temp;
	math3d_quaternion_to_mat3(q, &temp);
	math3d_mat3_to_mat4(&temp, m);
}

float math3d_quaternion_length(const struct math3d_quaternion *q)
{
	return sqrtf(q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z);
}

void math3d_quaternion_unit_inv(const struct math3d_quaternion *q, struct math3d_quaternion *q_inv)
{
	q_inv->w = q->w;
	q_inv->x = -q->x;
	q_inv->y = -q->y;
	q_inv->z = -q->z;
}

void math3d_quaternion_inv(const struct math3d_quaternion *q, struct math3d_quaternion *q_inv)
{
	float mag = math3d_quaternion_length(q);
	math3d_quaternion_unit_inv(q, q_inv);
	q_inv->w /= mag * mag;
	q_inv->x /= mag * mag;
	q_inv->y /= mag * mag;
	q_inv->z /= mag * mag;
}

void math3d_mat3_to_mat4(const struct math3d_mat3 *m1, struct math3d_mat4 *m2)
{
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			m2->v[i][j] = m1->v[i][j];
		}
	}
	m2->v[3][0] = 0;
	m2->v[3][1] = 0;
	m2->v[3][2] = 0;
	m2->v[3][3] = 0;
	m2->v[0][3] = 0;
	m2->v[1][3] = 0;
	m2->v[2][3] = 0;
}

void math3d_quaternion_mul(const struct math3d_quaternion *q1, const struct math3d_quaternion *q2, struct math3d_quaternion *q3)
{
	q3->w = (q1->w * q2->w  - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z);
	q3->x = (q1->w * q2->x + q1->x * q2->w  + q1->y * q2->z - q1->z * q2->y);
	q3->y = (q1->w * q2->y - q1->x * q2->z + q1->y * q2->w  + q1->z * q2->x);
	q3->z = (q1->w * q2->z + q1->x * q2->y - q1->y * q2->x + q1->z * q2->w);
}

void math3d_quaternion_mul_vec3(const struct math3d_quaternion *q, const struct math3d_vec3 *v1, struct math3d_vec3 *v2)
{
	struct math3d_mat3 temp;
	math3d_quaternion_to_mat3(q, &temp);
	math3d_mat3_mul_vec3(&temp, v1, v2);
}

void math3d_quaternion_unit_inv_mul_vec3(const struct math3d_quaternion *q, const struct math3d_vec3 *v1, struct math3d_vec3 *v2)
{
	struct math3d_mat3 temp;
	struct math3d_quaternion q_inv;
	math3d_quaternion_unit_inv(q, &q_inv);
	math3d_quaternion_to_mat3(&q_inv, &temp);
	math3d_mat3_mul_vec3(&temp, v1, v2);
}
