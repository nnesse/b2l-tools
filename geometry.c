#include "geometry.h"

#define GLB_ENABLE_GL_ARB_vertex_attrib_binding
#define GLB_ENABLE_GL_ARB_buffer_storage
#include "glb-glcore.h"

#include <stdint.h>

#include <math.h>

#include "lua.h"

void buffer_type_init(struct buffer_type *t)
{
	glGenVertexArrays(1, &t->vao);
	glBindVertexArray(t->vao);

	int pos;
	for (pos = 0; pos < NUM_ATTRIBUTES; pos++) {
		if (!t->attribute[pos].size)
			continue;
		glEnableVertexAttribArray(pos);
		glVertexAttribBinding(pos, 0);
		if (t->attribute[pos].integer) {
			glVertexAttribIFormat(pos,
				t->attribute[pos].size,
				t->attribute[pos].type,
				t->attribute[pos].offset);
		} else {
			glVertexAttribFormat(pos,
				t->attribute[pos].size,
				t->attribute[pos].type,
				GL_FALSE,
				t->attribute[pos].offset);
		}
	}
}

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

void create_geometry_begin(struct geometry *g, void ** const vertex_buffer, uint16_t ** const index_buffer)
{
	glGenBuffers(1, &g->vertex_array);
	glGenBuffers(1, &g->index_array);
	glBindBuffer(GL_ARRAY_BUFFER, g->vertex_array);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g->index_array);

	glBufferStorage(GL_ARRAY_BUFFER,
			g->type->element_size * g->num_verticies,
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

struct buffer_type buffer_type_mesh[2][6];

void create_mesh_geometry(struct geometry *g, lua_State *L, uint8_t *blob)
{
	lua_getfield(L, -1, "num_triangles");
	g->num_triangles = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "num_verticies");
	g->num_verticies = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "uv_layers");
	lua_len(L, -1);
	int num_uv_layers = lua_tointeger(L, -1);
	lua_pop(L, 2);

	lua_getfield(L, -1, "weights_per_vertex");
	int weights_per_vertex = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "submeshes");
	lua_len(L, -1);
	int num_submesh = lua_tointeger(L, -1);
	lua_pop(L, 1);

	g->num_submesh = num_submesh;

	int i;
	for (i = 1; i <= num_submesh; i++) {
		struct submesh *submesh = g->submesh + i - 1;
		lua_rawgeti(L, -1, i);
		lua_getfield(L, -1, "material_name");
		submesh->material_name = strdup(lua_tostring(L, -1));
		lua_pop(L, 1);

		lua_getfield(L, -1, "triangle_no");
		submesh->triangle_no = lua_tointeger(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, -1, "triangle_count");
		submesh->triangle_count = lua_tointeger(L, -1);
		lua_pop(L, 1);
		lua_pop(L, 1);
	}
	lua_pop(L, 1);

	int fcount = 0;

	struct buffer_type *type = &(buffer_type_mesh[(num_uv_layers > 0) ? 0 : 1][weights_per_vertex]);
	if (!type->element_size) {
		type->attribute[ATTRIBUTE_VERTEX].integer = false;
		type->attribute[ATTRIBUTE_VERTEX].size = 3;
		type->attribute[ATTRIBUTE_VERTEX].type = GL_FLOAT;
		type->attribute[ATTRIBUTE_VERTEX].offset = 0;
		fcount += 3;

		type->attribute[ATTRIBUTE_NORMAL].integer = false;
		type->attribute[ATTRIBUTE_NORMAL].size = 3;
		type->attribute[ATTRIBUTE_NORMAL].type = GL_FLOAT;
		type->attribute[ATTRIBUTE_NORMAL].offset = sizeof(float) * fcount;
		fcount += 3;

		if (num_uv_layers > 0) {
			type->attribute[ATTRIBUTE_UV].integer = false;
			type->attribute[ATTRIBUTE_UV].size = 2;
			type->attribute[ATTRIBUTE_UV].type = GL_FLOAT;
			type->attribute[ATTRIBUTE_UV].offset = sizeof(float) * fcount;
			fcount += 2;

			type->attribute[ATTRIBUTE_TANGENT].integer = false;
			type->attribute[ATTRIBUTE_TANGENT].size = 4;
			type->attribute[ATTRIBUTE_TANGENT].type = GL_FLOAT;
			type->attribute[ATTRIBUTE_TANGENT].offset = sizeof(float) * fcount;
			fcount += 4;
		}

		int scount = 0;

		for (i = 0; i < weights_per_vertex && i < 6; i++) {
			type->attribute[ATTRIBUTE_WEIGHT0 + i].integer = true;
			type->attribute[ATTRIBUTE_WEIGHT0 + i].size = 2;
			type->attribute[ATTRIBUTE_WEIGHT0 + i].type = GL_UNSIGNED_SHORT;
			type->attribute[ATTRIBUTE_WEIGHT0 + i].offset = sizeof(float) * fcount + sizeof(uint16_t) * scount;
			scount += 2;
		}

		type->element_size = sizeof(float) * fcount + sizeof(uint16_t) * scount;
		buffer_type_init(type);
	}
	g->type = type;

	float *vertex_buffer;
	uint16_t *index_buffer;

	create_geometry_begin(g, (void **)&vertex_buffer, &index_buffer);
	uint8_t *ptr = (uint8_t *) vertex_buffer;

	lua_getfield(L, -1, "vertex_co_array_offset");
	float *vertex_ptr = (float *)(blob + lua_tointeger(L, -1));
	lua_pop(L, 1);

	lua_getfield(L, -1, "vertex_normal_array_offset");
	float *normal_ptr = (float *)(blob + lua_tointeger(L, -1));
	lua_pop(L, 1);

	lua_getfield(L, -1, "uv_array_offset");
	float *uv_ptr = (float *)(blob + lua_tointeger(L, -1));
	lua_pop(L, 1);

	lua_getfield(L, -1, "tangent_array_offset");
	float *tangent_ptr = (float *)(blob + lua_tointeger(L, -1));
	lua_pop(L, 1);

	lua_getfield(L, -1, "weights_array_offset");
	uint16_t *weights_ptr = (uint16_t *)(blob + lua_tointeger(L, -1));
	lua_pop(L, 1);

	int j;
	for (i = 0; i < g->num_verticies; i++) {
		float *f = (float *)ptr;

		*(f++) = *(vertex_ptr++);
		*(f++) = *(vertex_ptr++);
		*(f++) = *(vertex_ptr++);

		*(f++) = *(normal_ptr++);
		*(f++) = *(normal_ptr++);
		*(f++) = *(normal_ptr++);

		if (num_uv_layers > 0) {
			*(f++) = *(uv_ptr++);
			*(f++) = *(uv_ptr++);

			*(f++) = *(tangent_ptr++);
			*(f++) = *(tangent_ptr++);
			*(f++) = *(tangent_ptr++);
			*(f++) = *(tangent_ptr++);
		}

		uint16_t *s = (uint16_t *)f;
		for (j = 0; j < weights_per_vertex && j < 6; j++) {
			s[2*j] = weights_ptr[2*j];
			s[2*j + 1] = weights_ptr[2*j + 1];
		}
		s += 2 * j;
		weights_ptr += 2 * weights_per_vertex;
		ptr += g->type->element_size;
	}

	lua_getfield(L, -1, "index_array_offset");
	memcpy(index_buffer, blob + lua_tointeger(L, -1), sizeof(uint16_t) * 3 * g->num_triangles);
	lua_pop(L, 1);

	create_geometry_end(g);
}

void render_geometry(struct geometry *g, int submesh)
{
	glBindVertexArray(g->type->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g->index_array);
	glBindVertexBuffer(0, g->vertex_array, 0, g->type->element_size);
	glDrawElements(GL_TRIANGLES,
		g->submesh[submesh].triangle_count * 3,
		GL_UNSIGNED_SHORT,
		(void *)(g->submesh[submesh].triangle_no * 3 * sizeof(uint16_t)));
}
