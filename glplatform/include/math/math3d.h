#ifndef MATH3D
#define MATH3D

struct math3d_quaternion {
	float x;
	float y;
	float z;
	float w;
};

struct math3d_mat4 {
	float v[4][4];
};

struct math3d_mat3 {
	float v[3][3];
};

struct math3d_vec4 {
	float v[4];
};

struct math3d_vec3 {
	float v[3];
};

struct math3d_ve22 {
	float v[2];
};

//
// math3d_mat4_mul(m1, m2, m3)
//
// m3 = m1 * m2
//
void math3d_mat4_mul(const struct math3d_mat4 *m1, const struct math3d_mat4 *m2, struct math3d_mat4 *m3);

//
// math3d_mat4_zero
//
// Zero a 4x4 matrix
//
void math3d_mat4_zero(struct math3d_mat4 *m);

//
// math3d_mat4_identity()
//
// Set a 4x4 matrix as an identity transform
//
void math3d_mat4_identity(struct math3d_mat4 *m);

//
// math3d_mat4_perspective(fovy, width, height, z_near, z_far, m)
//
// Construct perspective projection matrix
//
//   fovy - Field of view in the y direction in the range 0 to 1. A value
//
//          of 1 corresponds to 180 degrees
//
//   width - Width of viewport
//
//   height - Height of viewport
//
//   z_near - Location of near z clipping plane
//
//   z_far - Locaiton of far z clipping plane
 //
void math3d_mat4_perspective(float fovy, float width, float height, float z_near, float z_far, struct math3d_mat4 *m);

//
// math3d_mat4_ortho(x, y, z, width, height, depth, m)
//
// Construct an orthographic projection matrix
//
// x,y,z - Center of the cube to be projected
//
// width, height, depth - Size of the cube being projected
//
void math3d_mat4_ortho(float x, float y, float z, float width, float height, float depth, struct math3d_mat4 *m);

//
// math3d_vec3_dot(v1, v2)
//
// Returns v1 * v2
//
float math3d_vec3_dot(const struct math3d_vec3 *v1, const struct math3d_vec3 *v2);

//
// math3d_vec3_length(v)
//
// Returns the length of a vector
//
float math3d_vec3_length(const struct math3d_vec3 *v);

//
// math3d_vec3_cross(a, b, c)
//
// c = a x b
//
void math3d_vec3_cross(struct math3d_vec3 *a, struct math3d_vec3 *b, struct math3d_vec3 *c);

//
// math3d_vec3_lerp(v1, v2, d, v3)
//
// Linearly interpolate between v1 and v2
//
// v3 = v1 * (1 - d) + v2 * d
//
void math3d_vec3_lerp(const struct math3d_vec3 *v1, const struct math3d_vec3 *v2, float d, struct math3d_vec3 *v3);

//
// math3d_vec3_normalize(v)
//
// v = v / length(v)
//
void math3d_vec3_normalize(struct math3d_vec3 *v);

//
// math3d_spherical_lerp(v1, v2, d, v3)
//
// Spherical interpolatate between v1, v2 and store result in v3.
//
// Unlike linear interpolation with spherical interpolation the length of the vector is
// a linear function (or constant) but the path of the vector follows a spherical arc.
//
void math3d_spherical_lerp(const struct math3d_vec3 *v1, const struct math3d_vec3 *v2, float d, struct math3d_vec3 *v3);

//
// math3d_mat4_transpose(m, m_t)
//
// m_t = transpose(m)
//
void math3d_mat4_transpose(const struct math3d_mat4 *m, struct math3d_mat4 *m_t);

//
// math3d_mat4_mul_vec4(M, v1, v2)
//
// v2 = M * v1
//
void math3d_mat4_mul_vec4(const struct math3d_mat4 *M, const struct math3d_vec4 *v1, struct math3d_vec4 *v2);

//
// math3d_mat4_mul_vec3(M, v1, v2)
//
// v2 = M * v1
//

void math3d_mat3_mul_vec3(const struct math3d_mat3 *m, const struct math3d_vec3 *v1, struct math3d_vec3 *v2);

//
//math3d_quaternion_from_axis_angle()
//
void math3d_quaternion_from_axis_angle(struct math3d_quaternion *q, const struct math3d_vec3 *axis, float angle);

//
// math3d_quaternion_to_mat3()
//
void math3d_quaternion_to_mat3(const struct math3d_quaternion *q, struct math3d_mat3 *m);

//
// math3d_quaternion_to_mat4()
//
// Convert a quaternion to a 4x4 matrix
//
void math3d_quaternion_to_mat4(const struct math3d_quaternion *q, struct math3d_mat4 *m);

//
// math3d_quaternion_length(q)
//
// Returns the length of a quaternion
//
float math3d_quaternion_length(const struct math3d_quaternion *q);

//
// math3d_quaternion_unit_inv(q, q_inv)
//
// Computes the inverse of a unit length quaternian
//
// q_inv = q ^ -1
//
void math3d_quaternion_unit_inv(const struct math3d_quaternion *q, struct math3d_quaternion *q_inv);

//
// math3d_quaternion_inv(q, q_inv)
//
void math3d_quaternion_inv(const struct math3d_quaternion *q, struct math3d_quaternion *q_inv);

//
// math3d_mat3_to_mat4(m1, m2)
//
// Convert a 3x3 matrix to a 4x4 matrix by padding with zeros
//
void math3d_mat3_to_mat4(const struct math3d_mat3 *m1, struct math3d_mat4 *m2);

//
// math3d_quaternion_mul(q1, q2, q3)
//
// Multiply two quaternions together
//
// q3 = q1 * q2
//
void math3d_quaternion_mul(const struct math3d_quaternion *q1, const struct math3d_quaternion *q2, struct math3d_quaternion *q3);

//
// math3d_quaternion_mul_vec3(q, v1, v2)
//
// Multiply a vector times a quaternion
//
// v2 = q * v1
//
void math3d_quaternion_mul_vec3(const struct math3d_quaternion *q, const struct math3d_vec3 *v1, struct math3d_vec3 *v2);

//
// math3d_quaternion_unit_inv_mul_vec3()
//
// Multipy a a vector by a the inverse of a unit quaternion
//
void math3d_quaternion_unit_inv_mul_vec3(const struct math3d_quaternion *q, const struct math3d_vec3 *v1, struct math3d_vec3 *v2);

#endif
