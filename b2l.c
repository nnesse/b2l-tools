#include "b2l.h"

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "program.h"

#include <stdio.h>

#include "glsl_parser.h"
#include "glsl_ast.h"

#define GLPLATFORM_ENABLE_GL_ARB_vertex_attrib_binding
#define GLPLATFORM_ENABLE_GL_ARB_buffer_storage
#include "glplatform-glcore.h"

#include <gdk-pixbuf/gdk-pixbuf.h>

#include <glib.h>
#include <stdlib.h>

static char *filter_shader_text(lua_State *L, const char *input)
{
	char *output;
	struct glsl_parse_context context;
	glsl_parse_context_init(&context);
	glsl_parse_string(&context, input);
	output = glsl_ast_generate_glsl(context.root);
	glsl_parse_context_destroy(&context);
	lua_pushstring(L, "#version 330\n"); //TODO: we need to grab the actual text for this
	lua_pushstring(L, output);
	lua_concat(L, 2);
	free(output);
	output = strdup(lua_tostring(L, -1));
	lua_pop(L, 1);
	return output;
}

static uint8_t *get_file_buffer(const char *fname, size_t *size)
{
	FILE *f = fopen(fname, "rb");
	if (!f) {
		return NULL;
	}
	fseek(f, 0, SEEK_END);
	size_t fsize = ftell(f);
	fseek(f, 0, SEEK_SET);
	uint8_t *ret = (uint8_t *)malloc(fsize + 1);
	if (fread(ret, fsize, 1, f) != 1) {
		free(ret);
		fclose(f);
		return NULL;
	}
	ret[fsize] = 0;
	fclose(f);
	if (size)
		*size = fsize;
	return ret;
}

static void truncate_to_dirname(char *str)
{
	char *x = str;
	char *y = NULL;
	while (*x) {
		if (*x == '/')
			y = x;
		x++;
	}
	if (y)
		*(++y) = 0;
	else
		*str = 0;
}

bool b2l_load(lua_State *L, const char *b2l_file_name, void ** blob, size_t *blob_size)
{
	if (luaL_loadfile(L, b2l_file_name) != LUA_OK) {
		fprintf(stderr, "Failed to load B2L file %s\n", b2l_file_name);
		return false;
	}
	lua_call(L, 0, 1);

	char *b2l_mat_file_name = g_strdup_printf("%s.mat", b2l_file_name);
	if (luaL_loadfile(L, b2l_mat_file_name) != LUA_OK) {
		fprintf(stderr, "Failed to load B2L material file %s\n", b2l_mat_file_name);
		g_free(b2l_mat_file_name);
		return false;
	}
	lua_call(L, 0, 1);

	char *b2l_bin_file_name = g_strdup_printf("%s.bin", b2l_file_name);
	*blob = get_file_buffer(b2l_bin_file_name, blob_size);
	if (!*blob) {
		fprintf(stderr, "Failed to load bin file '%s'\n", b2l_bin_file_name);
		g_free(b2l_mat_file_name);
		g_free(b2l_bin_file_name);
		return false;
	}

	g_free(b2l_mat_file_name);
	g_free(b2l_bin_file_name);

	return true;
}

bool b2l_materials_gl_setup(lua_State *L, const char *b2l_file_name, int materials_idx)
{
	int prev_top = lua_gettop(L);
	bool ret = false;
	char *b2l_dir = strdup(b2l_file_name);
	truncate_to_dirname(b2l_dir);

	lua_pushnil(L);
	while(lua_next(L, materials_idx)) {
		int material_idx = lua_gettop(L);
		lua_getfield(L, material_idx, "program");

		//
		// Create material program object if it's missing
		//
		if (!lua_isuserdata(L, -1)) {
			lprogram_create(L);
			lua_setfield(L, material_idx, "program");
		}
		lua_getfield(L, material_idx, "program");
		int program_idx = lua_gettop(L);
		struct program *program = lua_touserdata(L, program_idx);

		lua_getfield(L, material_idx, "shaders");
		int shaders_idx = lua_gettop(L);

		lua_getfield(L, shaders_idx, "fs_filename");
		if (lua_isnil(L, -1)) {
			fprintf(stderr, "No fragment shader specified for material '%s'\n", lua_tostring(L, material_idx - 1));
			goto end;
		}

		lua_getfield(L, shaders_idx, "vs_filename");
		if (lua_isnil(L, -1)) {
			fprintf(stderr, "No vertex shader specified for material '%s'\n", lua_tostring(L, material_idx - 1));
			goto end;
		}

		char *abs_vs_filename = g_strdup_printf("%s%s", b2l_dir, lua_tostring(L, -1));
		char *abs_fs_filename = g_strdup_printf("%s%s", b2l_dir, lua_tostring(L, -2));
		char *vs_text_orig = (char *)get_file_buffer(abs_vs_filename, NULL);
		if (!vs_text_orig) {
			fprintf(stderr, "Failed to load vertex shader '%s'\n", abs_vs_filename);
			g_free(abs_vs_filename);
			g_free(abs_fs_filename);
			free(vs_text_orig);
			goto end;
		}
		char *fs_text_orig = (char *)get_file_buffer(abs_fs_filename, NULL);
		if (!fs_text_orig) {
			fprintf(stderr, "Failed to fragment vertex shader '%s'\n", abs_fs_filename);
			g_free(abs_vs_filename);
			g_free(abs_fs_filename);
			free(fs_text_orig);
			free(fs_text_orig);
			goto end;
		}
		char *vs_text = filter_shader_text(L, vs_text_orig);
		char *fs_text = filter_shader_text(L, fs_text_orig);

		lua_pushvalue(L, program_idx);
		if (!lprogram_set_shaders(L, vs_text, fs_text)) {
			fprintf(stderr, "Failed to compile shaders\n");
			g_free(abs_vs_filename);
			g_free(abs_fs_filename);
			free(vs_text_orig);
			free(fs_text_orig);
			free(vs_text);
			free(fs_text);
			goto end;
		}

		g_free(abs_vs_filename);
		g_free(abs_fs_filename);
		free(vs_text_orig);
		free(fs_text_orig);
		free(vs_text);
		free(fs_text);

		glUseProgram(program->program);

		//
		// Upload textures if neccisary
		//
		int texunit = 0;
		lua_getfield(L, material_idx, "params");
		lua_pushnil(L);  /* first key */
		while (lua_next(L, -2)) {
			int variable_idx = lua_gettop(L);
			lua_getfield(L, variable_idx, "datatype");
			const char *datatype = lua_tostring(L, -1);
			if (!strcmp(datatype,"sampler2D")) {
				lua_getfield(L, variable_idx, "_texid");

				GLuint texid = 0;
				if (lua_isnil(L, -1)) {
					const char *variable_name = lua_tostring(L, variable_idx - 1);
					int uniform_loc = glGetUniformLocation(program->program, variable_name);

					lua_getfield(L, variable_idx, "value");
					if (lua_isstring(L, -1)) {

						char *abs_filename = g_strdup_printf("%s%s", b2l_dir, lua_tostring(L, -1));

						GdkPixbuf *pbuf = gdk_pixbuf_new_from_file(abs_filename, NULL);
						if (pbuf) {
							//
							// Upload pbuf to texture
							//
							glActiveTexture(GL_TEXTURE0 + texunit);

							glGenTextures(1, &texid);
							glBindTexture(GL_TEXTURE_2D, texid);
							lua_pushinteger(L, texid);
							lua_setfield(L, variable_idx, "_texid");

							int width = gdk_pixbuf_get_width(pbuf);
							int height = gdk_pixbuf_get_height(pbuf);
							int n_chan = gdk_pixbuf_get_n_channels(pbuf);
							glPixelStorei(GL_UNPACK_ROW_LENGTH, gdk_pixbuf_get_rowstride(pbuf)/ n_chan);
							glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
							glTexImage2D(GL_TEXTURE_2D,
								0, /* level */
								n_chan > 3 ? GL_RGBA : GL_RGB,
								width,
								height,
								0, /* border */
								n_chan > 3 ? GL_RGBA : GL_RGB,
								GL_UNSIGNED_BYTE,
								gdk_pixbuf_get_pixels(pbuf));
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
							glGenerateMipmap(GL_TEXTURE_2D);
							glUniform1i(uniform_loc, texunit);
							g_object_unref(pbuf);
						} else {
							fprintf(stderr, "Failed to load image file: %s\n", abs_filename);
							goto end;
						}
						g_free(abs_filename);
					}
				}
				texunit++;

			}
			lua_settop(L, variable_idx - 1);
		}
		lua_settop(L, material_idx - 1);
	}
	ret = true;
end:
	lua_settop(L, prev_top);
	return ret;
}

bool b2l_is_mesh_object(lua_State *L, int b2l_data_idx, const char *object_name)
{
	int prev_top = lua_gettop(L);
	bool ret = false;
	lua_getfield(L, b2l_data_idx, "objects");
	lua_getfield(L, -1, object_name);
	if (lua_istable(L, -1)) {
		lua_getfield(L, -1, "type");
		ret = !strcmp(lua_tostring(L, -1), "MESH");
	}
	lua_settop(L, prev_top);
	return ret;
}
