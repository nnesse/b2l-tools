#ifndef GEOMETRY_H
#define GEOMETRY_H

#define GLPLATFORM_ENABLE_GL_ARB_vertex_attrib_binding
#define GLPLATFORM_ENABLE_GL_ARB_buffer_storage
#include "glplatform-glcore.h"

#include <stdint.h>
enum attributes {
	ATTRIBUTE_VERTEX,
	ATTRIBUTE_NORMAL,
	ATTRIBUTE_UV,
	ATTRIBUTE_TANGENT,
	ATTRIBUTE_WEIGHT0,
	ATTRIBUTE_WEIGHT1,
	ATTRIBUTE_WEIGHT2,
	ATTRIBUTE_WEIGHT3,
	ATTRIBUTE_WEIGHT4,
	ATTRIBUTE_WEIGHT5,
	NUM_ATTRIBUTES
};

struct attribute {
	bool integer;
	GLint size;
	GLenum type;
	GLuint offset;
};

struct buffer_type {
	GLuint vao;
	size_t element_size;
	struct attribute attribute[NUM_ATTRIBUTES];
};

struct submesh {
	const char *material_name;
	int triangle_count;
	int triangle_no;
};

struct geometry {
	struct buffer_type *type;
	int num_verticies;
	int num_triangles;
	int num_submesh;

	GLuint vertex_array;
	GLuint index_array;
	struct submesh submesh[];
};

#include "lua.h"

void create_geometry_begin(struct geometry *g, void ** const vertex_buffer, uint16_t ** const index_buffer);

void create_geometry_end(struct geometry *g);

void create_mesh_geometry(struct geometry *g, lua_State *L, uint8_t *blob);

void create_cylinder_geometry(struct geometry *g, int m, int n);

void create_cone_geometry(struct geometry *g, int n);

void render_geometry(struct geometry *g, int submesh);

void delete_geometry(struct geometry *g);

#endif
