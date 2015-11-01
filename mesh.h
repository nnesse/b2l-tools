#ifndef MESH_H
#define MESH_H

#include "vectormath.h"

#include "lua.h"

#include "geometry.h"

#include <stdint.h>

struct mesh {
	struct buffer_type *type;
	int num_verticies;
	int num_triangles;
	int num_submesh;
	int weights_per_vertex;
	int has_uv_layers;
	uint32_t vertex_array;
	uint32_t index_array;
	uint32_t uv_array[MAX_UV_LAYERS];
	struct submesh submesh[];
};

void render_mesh(lua_State *L, int b2l_data_idx, int materials_idx, const uint8_t *blob,
		const char *scene_name,
		const char *object_name,
		double frame,
		struct mat4 *model,
		struct mat4 *view,
		struct mat4 *proj);

void create_mesh(struct mesh *m, lua_State *L, const uint8_t *blob);

void render_submesh(struct mesh *m, int submesh, int uvmap);

#endif
