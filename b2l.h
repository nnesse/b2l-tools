#ifndef B2L_H
#define B2L_H

#include "lua.h"
#include <stdbool.h>

bool b2l_load(lua_State *L, const char *b2l_filename, void ** blob, size_t *blob_size);

bool b2l_materials_gl_setup(lua_State *L, const char *b2l_dir, int materials_idx);

bool b2l_is_mesh_object(lua_State *L, int b2l_data_idx, const char *object_name);

#endif
