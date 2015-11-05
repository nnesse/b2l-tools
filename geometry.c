#include "geometry.h"

#include "vectormath.h"

#include "program.h"

#include "glplatform-glcore.h"

#include <stdint.h>

#include <math.h>

#include "lua.h"

void buffer_type_init(struct buffer_type *t, struct attribute *attribute, int num_attributes)
{
	glGenVertexArrays(1, &t->vao);
	glBindVertexArray(t->vao);

	int pos;
	for (pos = 0; pos < num_attributes; pos++) {
		struct attribute *attrib = attribute + pos;
		if (!attribute[pos].size)
			continue;
		glEnableVertexAttribArray(pos);
		glVertexAttribBinding(pos, attrib->binding_index);
		if (attribute[pos].integer) {
			glVertexAttribIFormat(pos,
				attribute[pos].size,
				attribute[pos].type,
				attribute[pos].offset);
		} else {
			glVertexAttribFormat(pos,
				attribute[pos].size,
				attribute[pos].type,
				GL_FALSE,
				attribute[pos].offset);
		}
	}
	t->valid = 1;
}

#if 0
struct buffer_type buffer_type_v3f = {
	.element_size = 3 * sizeof(float),
	.attribute = {
		[ATTRIBUTE_VERTEX] = {
			.integer = false,
			.size = 3,
			.type = GL_FLOAT,
			.offset = 0
		}
	}
};
#endif

void create_geometry_begin(struct geometry *g, void ** const vertex_buffer, uint16_t ** const index_buffer)
{
	glGenBuffers(1, &g->vertex_array);
	glGenBuffers(1, &g->index_array);
	glBindBuffer(GL_ARRAY_BUFFER, g->vertex_array);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g->index_array);

	glBufferStorage(GL_ARRAY_BUFFER,
			g->type->element_size[0] * g->num_verticies,
			NULL,
			GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
	glBufferStorage(GL_ELEMENT_ARRAY_BUFFER,
			sizeof(uint16_t) * 3 * g->num_triangles,
			NULL,
			GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);


	*vertex_buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	*index_buffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void create_geometry_end(struct geometry *g)
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
}

void delete_geometry(struct geometry *g)
{
	glDeleteBuffers(1, &g->vertex_array);
	glDeleteBuffers(1, &g->index_array);
}

#if 0
void geometry_init()
{
	buffer_type_init(&buffer_type_v3f);
}

//
// m: Number of subdivisions of the unit circle
// n: Number of stacks
//
void create_cylinder_geometry(struct geometry *g, int m, int n)
{
	g->num_triangles = 2 * (m * (n + 1) - 1);
	g->num_verticies = m * (n + 1);
	g->type = &buffer_type_v3f;

	uint16_t *idx;
	float *r;

	create_geometry_begin(g, (void **)&r, &idx);

	int i, j;
	for (j = 0; j < (n + 1); j++) {
		float z = 1 - j * (2.0 / n);
		for (i = 0; i < m; i++) {
			float theta = i * ((2 * M_PI) / m);
			float x = sin(theta);
			float y = cos(theta);
			r[0] = x;
			r[1] = y;
			r[2] = z;
			r += 3;
			if (j < n) {
				idx[0] = m * j + i;
				idx[1] = m * (j + 1) + i;
				idx[2] = m * j + ((i + 1) % m);

				idx[3] = idx[1];
				idx[4] = idx[2];
				idx[5] = m * (j + 1) + ((i + 1) % m);
				idx += 6;
			}
		}
	}

	for (j = 1; j < m; j++) {
		idx[0] = 0;
		idx[1] = j;
		idx[2] = (j + 1) % m;
		idx[3] = idx[0] + m * n;
		idx[4] = idx[1] + m * n;
		idx[5] = idx[2] + m * n;
		idx += 6;
	}

	create_geometry_end(g);
}

void create_cone_geometry(struct geometry *g, int n)
{
	g->num_triangles = n * 2;
	g->num_verticies = n + 1;
	g->type = &buffer_type_v3f;

	uint16_t *idx;
	float *r;

	create_geometry_begin(g, (void **)&r, &idx);

	int i;
	for (i = 0; i < n; i++) {
		float theta = i * ((2 * M_PI) / n);
		float x = sin(theta);
		float z = cos(theta);
		float y = -1;
		r[0] = x;
		r[1] = y;
		r[2] = z;
		r += 3;
		idx[0] = i;
		idx[1] = n;
		idx[2] = (i + 1) % n;

		idx[3] = 0;
		idx[4] = (i + 1) % n;
		idx[5] = (i + 2) % n;
		idx += 6;
	}
	r[0] = 0;
	r[1] = 1;
	r[2] = 0;
	create_geometry_end(g);
}
#endif

void render_geometry(struct geometry *g)
{
	glBindVertexArray(g->type->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g->index_array);
	glBindVertexBuffer(0, g->vertex_array, 0, g->type->element_size[0]);
	glDrawElements(GL_TRIANGLES,
		g->triangle_count * 3,
		GL_UNSIGNED_SHORT,
		(void *)(g->triangle_no * 3 * sizeof(uint16_t)));
}
