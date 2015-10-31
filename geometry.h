#ifndef GEOMETRY_H
#define GEOMETRY_H

#define GLPLATFORM_ENABLE_GL_ARB_vertex_attrib_binding
#define GLPLATFORM_ENABLE_GL_ARB_buffer_storage
#include "glplatform-glcore.h"

#include <stdint.h>

#include "lua.h"
#include "vectormath.h"

#define MAX_VERTEX_WEIGHTS 6
#define MAX_UV_LAYERS 16
#define MAX_VERTEX_ATTRIB_BINDINGS 64

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
	int binding_index;
	bool integer;
	GLint size;
	GLenum type;
	GLuint offset;
};

struct buffer_type {
	GLuint vao;
	int valid;
	size_t element_size[MAX_VERTEX_ATTRIB_BINDINGS];
};

struct geometry {
	struct buffer_type *type;
	int num_verticies;
	int num_triangles;

	GLuint vertex_array;
	GLuint index_array;
	const char *material_name;
	int triangle_count;
	int triangle_no;
};

struct submesh {
	const char *material_name;
	int triangle_count;
	int triangle_no;
};

void buffer_type_init(struct buffer_type *t, struct attribute *attribute, int num_attributes);

void create_geometry_begin(struct geometry *g, void ** const vertex_buffer, uint16_t ** const index_buffer);

void create_geometry_end(struct geometry *g);

void create_cylinder_geometry(struct geometry *g, int m, int n);

void create_cone_geometry(struct geometry *g, int n);

void render_geometry(struct geometry *g);

void delete_geometry(struct geometry *g);

#endif
