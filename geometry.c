#include "geometry.h"

#define GLPLATFORM_ENABLE_GL_ARB_vertex_attrib_binding
#define GLPLATFORM_ENABLE_GL_ARB_buffer_storage
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

static struct buffer_type buffer_type_mesh[2][32];

void create_mesh(struct mesh *m, lua_State *L, uint8_t *blob)
{
	lua_getfield(L, -1, "num_triangles");
	m->num_triangles = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "num_verticies");
	m->num_verticies = lua_tointeger(L, -1);
	lua_pop(L, 1);

	int has_uv_layers = false;
	lua_getfield(L, -1, "uv_layers");
	lua_pushnil(L);
	if (lua_next(L, -2)) {
		has_uv_layers = true;
		lua_pop(L, 1);
	}
	lua_pop(L, 2);
	m->has_uv_layers = true;

	lua_getfield(L, -1, "weights_per_vertex");
	int weights_per_vertex = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "submeshes");
	lua_len(L, -1);
	int num_submesh = lua_tointeger(L, -1);
	lua_pop(L, 1);

	m->num_submesh = num_submesh;

	int i;
	for (i = 1; i <= num_submesh; i++) {
		struct submesh *submesh = m->submesh + i - 1;
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


	struct attribute attribute[NUM_ATTRIBUTES];

	memset(attribute, 0, sizeof(attribute));

	struct buffer_type *type = &(buffer_type_mesh[(has_uv_layers > 0) ? 1 : 0][weights_per_vertex]);
	if (!type->valid) {
		int fcount = 0;
		int scount = 0;
		attribute[ATTRIBUTE_VERTEX].integer = false;
		attribute[ATTRIBUTE_VERTEX].size = 3;
		attribute[ATTRIBUTE_VERTEX].type = GL_FLOAT;
		attribute[ATTRIBUTE_VERTEX].offset = 0;
		attribute[ATTRIBUTE_VERTEX].binding_index = 0;
		fcount += 3;

		attribute[ATTRIBUTE_NORMAL].integer = false;
		attribute[ATTRIBUTE_NORMAL].size = 3;
		attribute[ATTRIBUTE_NORMAL].type = GL_FLOAT;
		attribute[ATTRIBUTE_NORMAL].offset = sizeof(float) * fcount;
		attribute[ATTRIBUTE_NORMAL].binding_index = 0;
		fcount += 3;
		if (has_uv_layers) {
			attribute[ATTRIBUTE_UV].integer = false;
			attribute[ATTRIBUTE_UV].size = 2;
			attribute[ATTRIBUTE_UV].type = GL_FLOAT;
			attribute[ATTRIBUTE_UV].offset = 0;
			attribute[ATTRIBUTE_UV].binding_index = 1;
			attribute[ATTRIBUTE_TANGENT].integer = false;
			attribute[ATTRIBUTE_TANGENT].size = 4;
			attribute[ATTRIBUTE_TANGENT].type = GL_FLOAT;
			attribute[ATTRIBUTE_TANGENT].offset = sizeof(float) * 2;
			attribute[ATTRIBUTE_TANGENT].binding_index = 1;
		}

		for (i = 0; i < weights_per_vertex && i < MAX_VERTEX_WEIGHTS; i++) {
			attribute[ATTRIBUTE_WEIGHT0 + i].integer = true;
			attribute[ATTRIBUTE_WEIGHT0 + i].size = 2;
			attribute[ATTRIBUTE_WEIGHT0 + i].type = GL_UNSIGNED_SHORT;
			attribute[ATTRIBUTE_WEIGHT0 + i].offset = sizeof(float) * fcount + sizeof(uint16_t) * scount;
			attribute[ATTRIBUTE_WEIGHT0 + i].binding_index = 0;
			scount += 2;
		}

		type->element_size[0] = sizeof(float) * fcount + sizeof(uint16_t) * scount;
		type->element_size[1] = sizeof(float) * 6;
		buffer_type_init(type, attribute, NUM_ATTRIBUTES);
	}
	m->weights_per_vertex = weights_per_vertex;
	m->type = type;

	lua_getfield(L, -1, "vertex_co_array_offset");
	float *vertex_ptr = (float *)(blob + lua_tointeger(L, -1));
	lua_pop(L, 1);

	lua_getfield(L, -1, "vertex_normal_array_offset");
	float *normal_ptr = (float *)(blob + lua_tointeger(L, -1));
	lua_pop(L, 1);

	lua_getfield(L, -1, "weights_array_offset");
	uint16_t *weights_ptr = (uint16_t *)(blob + lua_tointeger(L, -1));
	lua_pop(L, 1);

	glGenBuffers(1, &m->vertex_array);
	glGenBuffers(1, &m->index_array);
	glGenBuffers(MAX_UV_LAYERS, m->uv_array);
	glBindBuffer(GL_ARRAY_BUFFER, m->vertex_array);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->index_array);

	glBufferStorage(GL_ARRAY_BUFFER,
			m->type->element_size[0] * m->num_verticies,
			NULL,
			GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
	glBufferStorage(GL_ELEMENT_ARRAY_BUFFER,
			sizeof(uint16_t) * 3 * m->num_triangles,
			NULL,
			GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);


	uint8_t *ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	uint16_t *index_buffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

	int j;
	for (i = 0; i < m->num_verticies; i++) {
		float *f = (float *)ptr;

		*(f++) = *(vertex_ptr++);
		*(f++) = *(vertex_ptr++);
		*(f++) = *(vertex_ptr++);

		*(f++) = *(normal_ptr++);
		*(f++) = *(normal_ptr++);
		*(f++) = *(normal_ptr++);

		uint16_t *s = (uint16_t *)f;
		for (j = 0; j < weights_per_vertex && j < MAX_VERTEX_WEIGHTS; j++) {
			s[2*j] = weights_ptr[2*j];
			s[2*j + 1] = weights_ptr[2*j + 1];
		}
		s += 2 * j;
		weights_ptr += 2 * weights_per_vertex;
		ptr += m->type->element_size[0];
	}
	lua_getfield(L, -1, "index_array_offset");
	memcpy(index_buffer, blob + lua_tointeger(L, -1), sizeof(uint16_t) * 3 * m->num_triangles);
	lua_pop(L, 1);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

	lua_getfield(L, -1, "uv_layers");
	lua_pushnil(L);
	i = 0;
	while (lua_next(L, -2)) {
		lua_pushinteger(L, i);
		lua_setfield(L, -2, "idx");

		lua_getfield(L, -1, "uv_array_offset");
		int uv_array_offset = lua_tointeger(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, -1, "tangent_array_offset");
		int tangent_array_offset = lua_tointeger(L, -1);
		lua_pop(L, 1);
		float *uv_ptr = (float *)(blob + uv_array_offset);
		float *tangent_ptr = (float *)(blob + tangent_array_offset);

		glBindBuffer(GL_ARRAY_BUFFER, m->uv_array[i]);
		glBufferStorage(GL_ARRAY_BUFFER, sizeof(float) * 6 * m->num_verticies, NULL, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
		ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		for (j = 0; j < m->num_verticies; j++) {
			float *f = (float *)ptr;
			*(f++) = *(uv_ptr++);
			*(f++) = *(uv_ptr++);
			*(f++) = *(tangent_ptr++);
			*(f++) = *(tangent_ptr++);
			*(f++) = *(tangent_ptr++);
			*(f++) = *(tangent_ptr++);
			ptr += m->type->element_size[1];
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
		lua_pop(L, 1);
		i++;
	}
	lua_pop(L, 2);
}

void render_mesh(struct mesh *m, int submesh, int uvmap)
{
	glBindVertexArray(m->type->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->index_array);
	glBindVertexBuffer(0, m->vertex_array, 0, m->type->element_size[0]);
	if (m->has_uv_layers)
		glBindVertexBuffer(1, m->uv_array[uvmap], 0, m->type->element_size[1]);
	glDrawElements(GL_TRIANGLES,
		m->submesh[submesh].triangle_count * 3,
		GL_UNSIGNED_SHORT,
		(void *)(m->submesh[submesh].triangle_no * 3 * sizeof(uint16_t)));
}

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

void delete_mesh(struct mesh *m)
{
	glDeleteBuffers(1, &m->vertex_array);
	glDeleteBuffers(1, &m->index_array);
	glDeleteBuffers(MAX_UV_LAYERS, m->uv_array);
}
