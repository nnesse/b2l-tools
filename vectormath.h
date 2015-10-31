#ifndef VECTORMATH_H
#define VECTORMATH_H

struct quaternion {
	float x;
	float y;
	float z;
	float w;
};

struct mat4 {
	float v[4][4];
};

struct mat3 {
	float v[3][3];
};

void mat4_mul(const struct mat4 *m1, const struct mat4 *m2, struct mat4 *m3);

float vec3_norm(const float *v);

void vec3_cross(const float *a, const float *b, float *c);

void lerp(const float *v1, const float *v2, float d, float *v3);

void vec3_normalize(float *v);

float vec3_dot(const float *v1, const float *v2);

void spherical_lerp(float *v1, float *v2, float d, float *vout);

void mat4_transpose(const struct mat4 *m, struct mat4 *out);

void mat4_mul_vec4(const struct mat4 *m, const float *v1, float *v2);

void mat3_mul_vec3(const struct mat3 *m, const float *v1, float *v2);

void mat4_zero(struct mat4 *m);

void mat4_identity(struct mat4 *m);

void quaternion_from_axis_angle(struct quaternion *q, float ax, float ay, float az, float angle);

void quaternion_to_mat3(const struct quaternion *q, struct mat3 *m);

void quaternion_to_mat4(const struct quaternion *q, struct mat4 *m);

void mat3_to_mat4(const struct quaternion *q, const struct mat3 *m1, struct mat4 *m2);

float quaternion_magnitude(const struct quaternion *q);

void quaternion_unit_inv(const struct quaternion *q, struct quaternion *q_inv);

void quaternion_inv(const struct quaternion *q, struct quaternion *q_inv);

void quaternion_mul(const struct quaternion *q1, const struct quaternion *q2, struct quaternion *out);

void quaternion_mul_vec3(const struct quaternion *q, const float *v1, float *v2);

void quaternion_unit_inv_mul_vec3(const struct quaternion *q, const float *v1, float *v2);

#endif
