#include "mesh.h"
#include <stdint.h>
#include <math.h>

#include "geometry.h"
#include "program.h"
#include "glplatform-glcore.h"
#include "lua.h"
#include "texture.h"
#include "math3d.h"

static void delete_mesh(struct mesh *m)
{
	glDeleteBuffers(1, &m->vertex_array);
	glDeleteBuffers(1, &m->index_array);
	glDeleteBuffers(MAX_UV_LAYERS, m->uv_array);
}

static int mesh_gc(lua_State *L)
{
	struct mesh *m = lua_touserdata(L, -1);
	if (m)
		delete_mesh(m);
	return 0;
}

static struct buffer_type buffer_type_mesh[2][32];

void create_mesh(struct mesh *m, lua_State *L, const uint8_t *blob)
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
		lua_pop(L, 3);
	} else {
		lua_pop(L, 1);
	}
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

void render_mesh(lua_State *L, int b2l_data_idx, int materials_idx, const uint8_t *blob,
		const char *scene_name,
		const char *object_name,
		double frame,
		struct math3d_mat4 *model,
		struct math3d_mat4 *view,
		struct math3d_mat4 *proj)
{
	int top_idx = lua_gettop(L);
	lua_getfield(L, b2l_data_idx, "objects");
	lua_getfield(L, -1, object_name);
	if (lua_isnil(L, -1)) {
		goto end;
	}
	int object_idx = lua_gettop(L);

	lua_getfield(L, object_idx, "type");
	if (strcmp(lua_tostring(L, -1), "MESH")) {
		goto end;
	}
	lua_getfield(L, object_idx, "data");
	lua_getfield(L, b2l_data_idx, "meshes");
	lua_getfield(L, -1, lua_tostring(L, -2));

	if (lua_isnil(L, -1)) {
		goto end;
	}

	int mesh_idx = lua_gettop(L);

	lua_getfield(L, mesh_idx, "mesh");
	struct mesh *m = (struct mesh *)lua_touserdata(L, -1);
	if (!m) {
		lua_getfield(L, mesh_idx, "submeshes");
		lua_len(L, -1);
		int num_submesh = lua_tointeger(L, -1);

		size_t mesh_size = offsetof(struct mesh, submesh[num_submesh]);
		m = (struct mesh *)lua_newuserdata(L, mesh_size);
		memset(m, 0, mesh_size);

		lua_newtable(L);
		lua_pushcfunction(L, mesh_gc);
		lua_setfield(L, -2, "__gc");
		lua_setmetatable(L, -2);

		lua_setfield(L, mesh_idx, "mesh");
		lua_pushvalue(L, mesh_idx);
		create_mesh(m, L, blob);
	}

	lua_getfield(L, object_idx, "vertex_groups");
	int num_vertex_groups;
	if (lua_isnil(L, -1)) {
		num_vertex_groups = 0;
	} else {
		lua_len(L, -1);
		num_vertex_groups = lua_tointeger(L, -1);
	}

	int i;
	for (i = 0; i < m->num_submesh; i++) {
		lua_getfield(L, materials_idx, m->submesh[i].material_name);
		int material_idx = lua_gettop(L);
		lua_getfield(L, material_idx, "program");

		struct program *program = lua_touserdata(L, -1);
		glUseProgram(program->program);
		glUniformMatrix4fv(glGetUniformLocation(program->program, "model"), 1, GL_FALSE, (GLfloat *)model);
		glUniformMatrix4fv(glGetUniformLocation(program->program, "proj"), 1, GL_FALSE, (GLfloat *)proj);
		glUniformMatrix4fv(glGetUniformLocation(program->program, "view"), 1, GL_FALSE, (GLfloat *)view);

		//
		// Compute armature matrix transforms
		//
		GLint groups_index = glGetUniformLocation(program->program, "groups");
		if (groups_index >= 0 && m->weights_per_vertex) {
			static int render_count = 0;
			render_count++;
			int prev_top = lua_gettop(L);
			int frame_i = floorf(frame);
			double frame_fract = frame - frame_i;

			lua_getfield(L, b2l_data_idx, "scenes");
			lua_getfield(L, -1, scene_name);
			if (!lua_istable(L, -1)) {
				goto end;
			}
			lua_getfield(L, -1, "objects");
			lua_getfield(L, -1, object_name);
			lua_getfield(L, -1, "vertex_group_transform_array_offset");
			int offset = lua_tointeger(L, -1);
			int stride = sizeof(float) * 4 * 4 * num_vertex_groups;
			int j;
			for (j = 0; j < num_vertex_groups; j++) {
				struct math3d_mat4 res;
				struct math3d_mat4 *base = (struct math3d_mat4 *)(blob + offset + (j * sizeof(float) * 4 * 4) + frame_i * stride);
				struct math3d_mat4 *next = (struct math3d_mat4 *)(blob + offset + (j * sizeof(float) * 4 * 4) + (frame_i + 1) * stride);

#if USE_SLERP
				struct math3d_mat4 M1;
				struct math3d_mat4 M2;
				struct math3d_mat4 temp;
				math3d_mat4_zero(&temp);
				temp.v[3][3] = 1;
				M1 = *base;
				M2 = *next;
				spherical_lerp(M1.v[0], M2.v[0], frame_fract, temp.v[0]);
				spherical_lerp(M1.v[1], M2.v[1], frame_fract, temp.v[1]);
				spherical_lerp(M1.v[2], M2.v[2], frame_fract, temp.v[2]);
				struct math3d_vec3 v1[3];
				struct math3d_vec3 v2[3];
				v1[0] = M1.v[0][3];
				v1[1] = M1.v[1][3];
				v1[2] = M1.v[2][3];
				v2[0] = M2.v[0][3];
				v2[1] = M2.v[1][3];
				v2[2] = M2.v[2][3];
				math3d_vec3_lerp(&v1, &v2, frame_fract, temp.v[3]);
#else
				math3d_mat4_lerp(base, next, frame_fract, &res);
#endif

				glUniformMatrix4fv(groups_index + j,
						1,
						GL_FALSE,
						(GLfloat *)&res);
			}
			lua_settop(L, prev_top);
		}

		int texunit = 0;

		//
		// Grab material state
		//
		lua_getfield(L, material_idx, "uv_layer");
		int uv_idx = 0;
		if (!lua_isnil(L, -1)) {
			lua_getfield(L, mesh_idx, "uv_layers");
			if (!lua_isnil(L, -1)) {
				lua_getfield(L, -1, lua_tostring(L, -2));
				if (!lua_isnil(L, -1)) {
					lua_getfield(L, -1, "idx");
					uv_idx = lua_tointeger(L , -1);
				}
			}
		}

		lua_getfield(L, material_idx, "params");
		lua_pushnil(L);  /* first key */
		while (lua_next(L, -2)) {
			int variable_idx = lua_gettop(L);
			const char *variable_name = lua_tostring(L, variable_idx - 1);
			int uniform_loc = glGetUniformLocation(program->program, variable_name);
			if (uniform_loc == -1) {
				lua_pop(L, 1);
				continue;
			}
			lua_getfield(L, variable_idx, "value");
			int value_idx = variable_idx + 1;
			lua_getfield(L, variable_idx, "datatype");
			const char *datatype = lua_tostring(L, -1);
			if (!strcmp(datatype, "bool")) {
				int bool_value = lua_toboolean(L, value_idx);
				glUniform1i(uniform_loc, bool_value);
			} else if (!strcmp(datatype, "vec3")) {
				lua_rawgeti(L, value_idx, 1);
				lua_rawgeti(L, value_idx, 2);
				lua_rawgeti(L, value_idx, 3);
				float val[3];
				val[0] = (float)lua_tonumber(L, -3);
				val[1] = (float)lua_tonumber(L, -2);
				val[2] = (float)lua_tonumber(L, -1);
				glUniform3fv(uniform_loc, 1, val);
			} else if (!strcmp(datatype, "float")) {
				float fval = lua_tonumber(L, value_idx);
				glUniform1f(uniform_loc, fval);
			} else if (!strcmp(datatype, "sampler2D")) {
				//
				// Bind texture
				//
				lua_getfield(L, variable_idx, "_texture");
				if (lua_isuserdata(L, -1)) {
					struct texture *t = lua_touserdata(L, -1);
					glActiveTexture(GL_TEXTURE0 + texunit);
					glBindTexture(GL_TEXTURE_2D, t->texid);
					glUniform1i(uniform_loc, texunit);
				}
				texunit++;
			}
			lua_settop(L, variable_idx - 1);
		}
		render_submesh(m, i, uv_idx);
		lua_pop(L, 1);
	}
end:
	lua_settop(L, top_idx);
}

void render_submesh(struct mesh *m, int submesh, int uvmap)
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
