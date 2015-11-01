#include "vectormath.h"
#include <math.h>
#include <memory.h>

void mat4_mul(const struct mat4 *m1, const struct mat4 *m2, struct mat4 *m3)
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

float vec3_norm(const float *v)
{
	return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void vec3_cross(const float *a, const float *b, float *c)
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = -a[0] * b[2] + a[2] * b[0];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

void lerp(const float *v1, const float *v2, float d, float *v3)
{
	int i;
	for (i = 0; i < 3; i++) {
		v3[i] = v1[i] * (1-d) + v2[i] * d;
	}
}

void vec3_normalize(float *v)
{
	int i;
	float norm = vec3_norm(v);
	if (norm > 0) {
		for (i = 0; i < 3; i++) {
			v[i] *= 1.0/norm;
		}
	}
}

float vec3_dot(const float *v1, const float *v2)
{
	int i;
	float ret = 0;
	for (i = 0; i < 3; i++) {
		ret += v1[i] * v2[i];
	}
	return ret;
}

void spherical_lerp(float *v1, float *v2, float d, float *vout)
{
	float v1xv2[3];
	float v3[3];

	float v1_norm = vec3_norm(v1);
	float v2_norm = vec3_norm(v2);
	vec3_normalize(v1);
	vec3_normalize(v2);

	vec3_cross(v1, v2, v1xv2);

	double theta;

	float dot = vec3_dot(v1, v2);
	if (dot > 1) dot = 1;
	theta = acosf(dot);

	if (theta < 0.05) {
		lerp(v1, v2, d, vout);
		return;
	}

	double phi = d * theta;

	vec3_normalize(v1xv2);
	vec3_cross(v1xv2, v1, v3);

	int i = 0;
	float cos_phi = cos(phi);
	float sin_phi = sin(phi);
	for (i = 0; i < 3; i++) {
		vout[i] = (cos_phi * v1[i] + sin_phi * v3[i]) * (v1_norm * (1-d) + v2_norm * d);
	}
}

void mat4_transpose(const struct mat4 *m, struct mat4 *out)
{
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			out->v[i][j] = m->v[j][i];
		}
	}
}

void mat4_mul_vec4(const struct mat4 *m, const float *v1, float *v2)
{
	int i, j;
	for (i = 0; i < 4; i++) {
		v2[i] = 0;
		for (j = 0; j < 4; j++) {
			v2[i] += m->v[j][i] * v1[j];
		}
	}
}

void mat3_mul_vec3(const struct mat3 *m, const float *v1, float *v2)
{
	int i, j;
	for (i = 0; i < 3; i++) {
		v2[i] = 0;
		for (j = 0; j < 3; j++) {
			v2[i] += m->v[j][i] * v1[j];
		}
	}
}

void quaternion_from_axis_angle(struct quaternion *q, float ax, float ay, float az, float angle)
{
	q->x = ax * sin(angle/2);
	q->y = ay * sin(angle/2);
	q->z = az * sin(angle/2);
	q->w = cos(angle/2);
}

void quaternion_to_mat3(const struct quaternion *q, struct mat3 *m)
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

void quaternion_to_mat4(const struct quaternion *q, struct mat4 *m)
{
	struct mat3 temp;
	quaternion_to_mat3(q, &temp);
	mat3_to_mat4(q, &temp, m);
}

float quaternion_magnitude(const struct quaternion *q)
{
	return sqrtf(q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z);
}

void quaternion_unit_inv(const struct quaternion *q, struct quaternion *q_inv)
{
	q_inv->w = q->w;
	q_inv->x = -q->x;
	q_inv->y = -q->y;
	q_inv->z = -q->z;
}

void quaternion_inv(const struct quaternion *q, struct quaternion *q_inv)
{
	float mag = quaternion_magnitude(q);
	quaternion_unit_inv(q, q_inv);
	q_inv->w /= mag * mag;
	q_inv->x /= mag * mag;
	q_inv->y /= mag * mag;
	q_inv->z /= mag * mag;
}

void mat3_to_mat4(const struct quaternion *q, const struct mat3 *m1, struct mat4 *m2)
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

void mat4_zero(struct mat4 *m)
{
	memset(m, 0, sizeof(*m));
}

void mat4_identity(struct mat4 *m)
{
	mat4_zero(m);
	m->v[0][0] = 1;
	m->v[1][1] = 1;
	m->v[2][2] = 1;
	m->v[3][3] = 1;
}

void quaternion_mul(const struct quaternion *q1, const struct quaternion *q2, struct quaternion *out)
{
	out->w = (q1->w * q2->w  - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z);
	out->x = (q1->w * q2->x + q1->x * q2->w  + q1->y * q2->z - q1->z * q2->y);
	out->y = (q1->w * q2->y - q1->x * q2->z + q1->y * q2->w  + q1->z * q2->x);
	out->z = (q1->w * q2->z + q1->x * q2->y - q1->y * q2->x + q1->z * q2->w);
}

void quaternion_mul_vec3(const struct quaternion *q, const float *v1, float *v2)
{
	struct mat3 temp;
	quaternion_to_mat3(q, &temp);
	mat3_mul_vec3(&temp, v1, v2);
}

void quaternion_unit_inv_mul_vec3(const struct quaternion *q, const float *v1, float *v2)
{
	struct mat3 temp;
	struct quaternion q_inv;
	quaternion_unit_inv(q, &q_inv);
	quaternion_to_mat3(&q_inv, &temp);
	mat3_mul_vec3(&temp, v1, v2);
}
