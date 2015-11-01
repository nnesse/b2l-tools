#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <getopt.h>

#include <gtk/gtk.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#define GLPLATFORM_ENABLE_GL_ARB_vertex_attrib_binding
#define GLPLATFORM_ENABLE_GL_ARB_buffer_storage
#include "glplatform-glcore.h"
#include "glsl_parser.h"
#include "glsl_ast.h"

#include "mesh.h"
#include "geometry.h"
#include "program.h"
#include "vectormath.h"

extern char *metalval;

#include <gdk-pixbuf/gdk-pixbuf.h>

#include <glib.h>
#include <glib-unix.h>
#include <glplatform.h>

#define MAX_TEXTURE_UNITS 8

#define USE_SLERP 1

#define NEW_STRUCT(TYPE) ((struct TYPE *)malloc(sizeof(struct TYPE), sizeof(intptr_t)))

static int make_path_relative(lua_State *L);
static int directory_name(lua_State *L);

static glplatform_gl_context_t g_ctx;
static struct glplatform_win *g_win;
static int g_dx[3];
static int g_dy[3];
static float g_log_zoom = 0.3;
static bool g_mouse_down[3] = {false, false, false};

static void on_expose(struct glplatform_win *win);
static void on_destroy(struct glplatform_win *win);
static void on_mouse_button_up(struct glplatform_win *, int, int, int);
static void on_mouse_button_down(struct glplatform_win *, int, int, int);
static void on_mouse_move(struct glplatform_win *, int, int);
static void on_resize(struct glplatform_win *);
static void on_mouse_wheel(struct glplatform_win *, int, int, int);

static struct quaternion q_cur = {0,0,0,1};
static struct quaternion q_delta = {0,0,0,1};
static float g_offset[3] = {0,0,0};
static float g_offset_next[3] = {0,0,0};

static void on_mouse_button_up(struct glplatform_win *win, int button, int x, int y)
{
	if (g_mouse_down[0] && button == 1) {
		struct quaternion next;
		quaternion_mul(&q_delta, &q_cur, &next);
		q_cur = next;
		q_delta.x = 0;
		q_delta.y = 0;
		q_delta.z = 0;
		q_delta.w = 1;
	}
	if (g_mouse_down[2] && button == 3) {
		g_offset[0] += g_offset_next[0];
		g_offset[1] += g_offset_next[1];
		g_offset[2] += g_offset_next[2];
		g_offset_next[0] = 0;
		g_offset_next[1] = 0;
		g_offset_next[2] = 0;
	}
	g_mouse_down[button -1] = false;
	on_mouse_move(win, x, y);
}

static void on_mouse_button_down(struct glplatform_win *win, int button, int x, int y)
{
	g_mouse_down[button -1] = true;
	g_dx[button - 1] = x;
	g_dy[button - 1] = y;
	on_mouse_move(win, x, y);
}

static void on_mouse_move(struct glplatform_win *win, int x, int y)
{
	struct quaternion next;
	quaternion_mul(&q_delta, &q_cur, &next);
	if (g_mouse_down[0]) {
		float axis[3];
		axis[0] = g_dy[0] - y;
		axis[1] = g_dx[0] - x;
		axis[2] = 0;
		float norm = sqrtf((axis[0] * axis[0]) + (axis[1] * axis[1]) + (axis[2] * axis[2]));
		if (norm > 0) {
			axis[0] /= norm;
			axis[1] /= norm;
			axis[2] /= norm;
		}
		quaternion_from_axis_angle(&q_delta, axis[0], axis[1], axis[2], norm * 3 / win->width);
	}
	if (g_mouse_down[2]) {
		float delta[3];
		delta[0] = (g_dx[2] - x) * 2.0 / win->width;
		delta[1] = -(g_dy[2] - y) * 2.0 / win->height;
		delta[2] = 0;
		quaternion_unit_inv_mul_vec3(&next, delta, g_offset_next);
		g_offset_next[0] = -g_offset_next[0];
		g_offset_next[1] = -g_offset_next[1];
		g_offset_next[2] = -g_offset_next[2];
	}
}

static void on_expose(struct glplatform_win *win)
{
}

static void on_mouse_wheel(struct glplatform_win *win, int x, int y, int direction)
{
	g_log_zoom  += direction * 0.1;
}

static int lua_backtrace_string(lua_State *L)
{
	static lua_Debug ar;
	int i = 0;
	while (lua_getstack(L, i++, &ar)) {
		lua_getinfo(L, "Sl", &ar);
		char *str = g_strdup_printf("%s:%d\n", ar.source, ar.currentline);
		lua_pushstring(L, str);
		g_free(str);
	}
	lua_concat(L, i -1);
	return 1;
}

static int make_path_relative(lua_State *L)
{
	if (!lua_isstring(L, -1) || !lua_isstring(L, -2)) {
		lua_pushnil(L);
		return 1;
	}
	const char *x = lua_tostring(L, -1); //file
	const char *y = lua_tostring(L, -2); //origin path (with trailing '/')
	int strings = 1;
	while (*x && *x == *y) {
		x++;
		y++;
	}
	while (*y) {
		if (*(y++) == '/') {
			lua_pushstring(L, "../");
			strings++;
		}
	}
	lua_pushstring(L, x);
	lua_concat(L, strings);
	return 1;
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

static int directory_name(lua_State *L)
{
	char *filename = strdup(lua_tostring(L, -1));
	truncate_to_dirname(filename);
	lua_pushstring(L, filename);
	free(filename);
	return 1;
}

static void on_resize(struct glplatform_win *win)
{
}

static void on_destroy(struct glplatform_win *win)
{
	exit(0);
}

struct glplatform_win_callbacks cb;

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

char *filter_shader_text(lua_State *L, const char *input)
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
	//glsl_ast_print(context.root, 0);
	//printf("%s\n", output);
	return output;
}

struct gl_state {
	bool initialized;
} g_gl_state;

static void init_gl_state(lua_State *L, const char *b2l_dir, int materials_idx)
{
	printf("OpenGL version %s\n", glGetString(GL_VERSION));

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
			return;
		}

		lua_getfield(L, shaders_idx, "vs_filename");
		if (lua_isnil(L, -1)) {
			fprintf(stderr, "No vertex shader specified for material '%s'\n", lua_tostring(L, material_idx - 1));
			return;
		}

		char *abs_vs_filename = g_strdup_printf("%s%s", b2l_dir, lua_tostring(L, -1));
		char *abs_fs_filename = g_strdup_printf("%s%s", b2l_dir, lua_tostring(L, -2));
		char *vs_text_orig = (char *)get_file_buffer(abs_vs_filename, NULL);
		if (!vs_text_orig) {
			fprintf(stderr, "Failed to load vertex shader '%s'\n", abs_vs_filename);
			return;
		}
		char *fs_text_orig = (char *)get_file_buffer(abs_fs_filename, NULL);
		if (!fs_text_orig) {
			fprintf(stderr, "Failed to fragment vertex shader '%s'\n", abs_fs_filename);
			return;
		}
		char *vs_text = filter_shader_text(L, vs_text_orig);
		char *fs_text = filter_shader_text(L, fs_text_orig);

		lua_pushvalue(L, program_idx);
		if (!lprogram_set_shaders(L, vs_text, fs_text)) {
			fprintf(stderr, "Failed to compile shaders\n");
			return;
		}

		g_free(abs_vs_filename);
		g_free(abs_fs_filename);
		free(vs_text_orig);
		free(fs_text_orig);
		free(vs_text);
		free(fs_text);

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
						} else {
							fprintf(stderr, "Failed to load image file: %s\n", abs_filename);
							return;
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
	g_gl_state.initialized = true;
}

static void redraw(lua_State *L, struct glplatform_win *win,
		const char *b2l_dir,
		int b2l_data_idx, int materials_idx, void *blob,
		double frame,
		const char *scene_name,
		const char *object_name)
{
	struct glplatform_thread_state thread_state;
	glplatform_get_thread_state(&thread_state);
	glplatform_make_current(win, g_ctx);

	static bool gl_init_attempted = false;
	static bool gl_init_result = false;

	if (!gl_init_attempted) {
		gl_init_result = glplatform_glcore_init(3, 3);
	}
	if (!gl_init_result) {
		fprintf(stderr, "Failed to initialize OpenGL bindings\n");
		exit(-1);
		return;
	}
	if (!GLPLATFORM_GL_ARB_buffer_storage) {
		fprintf(stderr, "Missing GL extension: GL_ARB_buffer_storage\n");
		exit(-1);
	}
	if (!GLPLATFORM_GL_ARB_vertex_attrib_binding) {
		fprintf(stderr, "Missing GL extension: GL_ARB_vertex_attrib_binding\n");
		exit(-1);
	}

	glViewport(0, 0, win->width, win->height);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	int top_idx = lua_gettop(L);

	if (!g_gl_state.initialized)
		init_gl_state(L, b2l_dir, materials_idx);

	if (!g_gl_state.initialized) {
		goto end;
	}

	struct mat4 view;
	struct mat4 model;
	struct mat4 proj;
	struct quaternion next;

	quaternion_mul(&q_delta, &q_cur, &next);
	quaternion_to_mat4(&next, &view);
	view.v[3][3] = 1;
	mat4_identity(&model);
	model.v[3][0] = g_offset[0] + g_offset_next[0];
	model.v[3][1] = g_offset[1] + g_offset_next[1];
	model.v[3][2] = g_offset[2] + g_offset_next[2];

	float zoom = exp(g_log_zoom);
	float zr = 100;
	mat4_zero(&proj);
	proj.v[0][0] = 1.0/zoom;
	proj.v[1][1] = 1.0*win->width/(zoom*win->height);
	proj.v[2][2] = 1.0/zr;
	proj.v[3][3] = 1.0;

	if (lua_isnil(L, -1))
		goto end;

	render_mesh(L, b2l_data_idx, materials_idx, blob,
			scene_name,
			object_name,
			frame,
			&model,
			&view,
			&proj);
end:
	lua_settop(L, top_idx);
	{
		GLenum err = glGetError();
		if (err)
			printf("render_scene GL error = %d\n", err);
	}
	glplatform_swap_buffers(g_win);
	glplatform_set_thread_state(&thread_state);
	return;
}

static void *l_alloc(void *ud, void *ptr, size_t osize, size_t nsize)
{
	(void)ud;
	(void)osize;  /* not used */
	if (nsize == 0) {
		free(ptr);
		return NULL;
	} else {
	   return realloc(ptr, nsize);
	}
}

int lua_panic_handler (lua_State* L)
{
	lua_pushvalue(L, -1);
	lua_pushstring(L, "\n");
	lua_backtrace_string(L);
	lua_concat(L, 3);
	fprintf(stderr, "%s\n", lua_tostring(L, -1));
	return 1;
}

int lua_message_handler (lua_State* L)
{
	lua_pushvalue(L, -1);
	lua_pushstring(L, "\n");
	lua_backtrace_string(L);
	lua_concat(L, 3);
	return 1;
}

static void print_help(const char *program_name)
{
	printf("Usage: %s [OPTION]... filename\n", program_name);
	printf("\n"
	       "Options:\n"
	       "  -f,--frame                         Frame number to render.\n"
	       "  -s,--scene name                    Scene to use.\n"
	       "  -o,--object name                   Object to render.\n"
	       "  -h,--help                          Print this page.\n");
}

bool is_mesh_object(lua_State *L, int b2l_data_idx, const char *object_name)
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

int main(int argc, char **argv)
{
	/*
	char exe_path[200];
	ssize_t sz = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);

	if (sz < 0)
		return -1;

	exe_path[sz] = '\0';

	truncate_to_dirname(exe_path);
	*/
	const char *b2l_file_name = NULL;
	const char *object_name = NULL;
	const char *scene_name = NULL;

	static struct option options [] = {
		{"help"   , 0, 0, 'h' },
		{"frame"  , 1, 0, 'f' },
		{"object" , 1, 0, 'o' },
		{"scene"  , 1, 0, 's' }
	};

	float frame = 1;
	char *temp;
	while (1) {
		int option_index;
		int c = getopt_long(argc, argv, "hf:o:s:", options, &option_index);
		if (c == -1) {
			break;
		}
		switch(c) {
		case '?':
		case ':':
			print_help(argv[0]);
			exit(-1);
			break;
		case 'h':
			print_help(argv[0]);
			exit(0);
			break;
		case 'f':
			temp = optarg;
			frame = strtod(optarg, &temp);
			if (temp == optarg || *temp != 0) {
				fprintf(stderr, "Invalid frame number: %s\n", optarg);
				print_help(argv[0]);
				exit(-1);
			}
			break;
		case 'o':
			object_name = optarg;
			break;
		case 's':
			scene_name = optarg;
			break;
		}
	}

	if (optind < argc) {
		b2l_file_name = argv[optind];
	} else {
		fprintf(stderr, "Missing B2L filename\n");
		print_help(argv[0]);
		exit(-1);
	}

	char *b2l_dir = strdup(b2l_file_name);
	truncate_to_dirname(b2l_dir);

	cb.on_expose = on_expose;
	cb.on_destroy = on_destroy;
	cb.on_resize = on_resize;
	cb.on_mouse_button_up = on_mouse_button_up;
	cb.on_mouse_button_down = on_mouse_button_down;
	cb.on_mouse_move = on_mouse_move;
	cb.on_mouse_wheel = on_mouse_wheel;
	cb.on_resize = on_resize;
	glplatform_init();

	lua_State *L = lua_newstate(l_alloc, NULL);
	luaL_openlibs(L);

	lua_atpanic(L, lua_panic_handler);

	lua_checkstack(L, 4096);

	lua_pushcfunction(L, lua_message_handler);
	int msgh = lua_gettop(L);

	if (luaL_loadfile(L, b2l_file_name) != LUA_OK) {
		fprintf(stderr, "Failed to load B2L file %s\n", b2l_file_name);
		exit(-1);
	}
	int err = lua_pcall(L, 0, 1, msgh);
	if (err != LUA_OK) {
		fprintf(stderr, "Lua error processing '%s': %s\n", b2l_file_name, lua_tostring(L, -1));
		exit(-1);
	}
	int b2l_data_idx = lua_gettop(L);

	char *b2l_mat_file_name = g_strdup_printf("%s.mat", b2l_file_name);
	if (luaL_loadfile(L, b2l_mat_file_name) != LUA_OK) {
		fprintf(stderr, "Failed to load B2L material file %s\n", b2l_mat_file_name);
		exit(-1);
	}
	err = lua_pcall(L, 0, 1, msgh);
	if (err != LUA_OK) {
		fprintf(stderr, "Lua error processing '%s': %s\n", b2l_mat_file_name, lua_tostring(L, -1));
		exit(-1);
	}
	int materials_idx = lua_gettop(L);

	lua_getfield(L, b2l_data_idx, "scenes");
	int scenes_idx = lua_gettop(L);

	if (object_name && !is_mesh_object(L, b2l_data_idx, object_name)) {
		fprintf(stderr, "Object '%s' is not a mesh object\n", object_name);
		exit(-1);
	}

	if (!scene_name) {
		lua_getfield(L, b2l_data_idx, "scenes");
		lua_pushnil(L);
		bool object_found = false;
		while (lua_next(L, -2)) {
			int scene_idx = lua_gettop(L);
			const char *tmp_scene_name = lua_tostring(L, -2);
			lua_getfield(L, scene_idx, "objects");

			if (object_name) {
				lua_getfield(L, -1, object_name);
				if (lua_istable(L, -1)) {
					object_found = true;
					scene_name = tmp_scene_name;
					break;
				}
			} else {
				lua_pushnil(L);
				while (lua_next(L, -2)) {
					const char *tmp_object_name = lua_tostring(L, -2);
					if (is_mesh_object(L, b2l_data_idx, tmp_object_name)) {
						object_found = true;
						object_name = tmp_object_name;
						break;
					}
					lua_pop(L, 1);
				}
				if (object_found) {
					scene_name = tmp_scene_name;
					break;
				}
			}
			lua_settop(L, scene_idx - 1);
		}
		if (!object_found) {
			fprintf(stderr, "No renderable scenes in file\n");
			exit(-1);
		}
	} else {
		lua_getfield(L, scenes_idx, scene_name);
		if (!lua_istable(L, -1)) {
			fprintf(stderr, "Scene '%s' not found\n", scene_name);
			exit(-1);
		}
		int scene_idx = lua_gettop(L);

		if (!object_name) {
			lua_getfield(L, scene_idx, "objects");
			lua_pushnil(L);
			while (lua_next(L, -2)) {
				int object_idx = lua_gettop(L);
				const char *tmp_object_name = lua_tostring(L, -2);
				if (is_mesh_object(L, b2l_data_idx, tmp_object_name)) {
					object_name = tmp_object_name;
					break;
				}
				lua_settop(L, object_idx -1);
			}
			if (!object_name) {
				fprintf(stderr, "No mesh objects found in scene '%s'\n", scene_name);
				exit(-1);
			}
		}
	}

	char *b2l_bin_file_name = g_strdup_printf("%s.bin", b2l_file_name);
	size_t blob_size;
	void *blob = get_file_buffer(b2l_bin_file_name, &blob_size);

	g_win = glplatform_create_window("B2L Model viewer", &cb, NULL, 512, 512);
	if (!g_win) {
		fprintf(stderr, "Unable to create GL enabled window\n");
		exit(-1);
	}

	glplatform_show_window(g_win);

	g_ctx = glplatform_create_context(g_win, 3, 3);
	if (!g_ctx)
		exit(-1);
	glplatform_make_current(g_win, g_ctx);

	while (glplatform_process_events()) {
		redraw(L, g_win, b2l_dir, b2l_data_idx, materials_idx, blob, frame, scene_name, object_name);
		lua_gc(L, LUA_GCCOLLECT, 0);
		glplatform_get_events(true);
	}
	g_free(b2l_bin_file_name);
	g_free(b2l_mat_file_name);
	return 0;
}
