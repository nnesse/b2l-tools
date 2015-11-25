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

#include <glplatform/glplatform-glcore.h>
#include <glplatform/math3d.h>
#include <glplatform/glplatform.h>
#include "b2l.h"

#include <glib.h>
#include "mesh.h"

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

static struct math3d_quaternion q_cur = {0,0,0,1};
static struct math3d_quaternion q_delta = {0,0,0,1};
static struct math3d_vec3 g_offset = {{0,0,0}};
static struct math3d_vec3 g_offset_next = {{0,0,0}};

static void on_mouse_button_up(struct glplatform_win *win, int button, int x, int y)
{
	if (g_mouse_down[0] && button == 1) {
		struct math3d_quaternion next;
		math3d_quaternion_mul(&q_delta, &q_cur, &next);
		q_cur = next;
		q_delta.x = 0;
		q_delta.y = 0;
		q_delta.z = 0;
		q_delta.w = 1;
	}
	if (g_mouse_down[2] && button == 3) {
		g_offset.v[0] += g_offset_next.v[0];
		g_offset.v[1] += g_offset_next.v[1];
		g_offset.v[2] += g_offset_next.v[2];
		g_offset_next.v[0] = 0;
		g_offset_next.v[1] = 0;
		g_offset_next.v[2] = 0;
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
	struct math3d_quaternion next;
	math3d_quaternion_mul(&q_delta, &q_cur, &next);
	if (g_mouse_down[0]) {
		struct math3d_vec3 axis;
		axis.v[0] = g_dy[0] - y;
		axis.v[1] = g_dx[0] - x;
		axis.v[2] = 0;
		float length = math3d_vec3_length(&axis);
		math3d_vec3_normalize(&axis);
		math3d_quaternion_from_axis_angle(&q_delta, &axis, length * 3 / win->width);
	}
	if (g_mouse_down[2]) {
		struct math3d_vec3 delta;
		delta.v[0] = (g_dx[2] - x) * 2.0 / win->width;
		delta.v[1] = -(g_dy[2] - y) * 2.0 / win->height;
		delta.v[2] = 0;
		math3d_quaternion_unit_inv_mul_vec3(&next, &delta, &g_offset_next);
		g_offset_next.v[0] = -g_offset_next.v[0];
		g_offset_next.v[1] = -g_offset_next.v[1];
		g_offset_next.v[2] = -g_offset_next.v[2];
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

static void on_resize(struct glplatform_win *win)
{
}

static void on_destroy(struct glplatform_win *win)
{
	exit(0);
}

struct glplatform_win_callbacks cb;

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

int main(int argc, char **argv)
{
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

	size_t blob_size;
	void *blob;
	if (!b2l_load(L, b2l_file_name, &blob, &blob_size)) {
		exit(-1);
	}
	int b2l_data_idx = lua_gettop(L) - 1;
	int materials_idx = lua_gettop(L);

	lua_getfield(L, b2l_data_idx, "scenes");
	int scenes_idx = lua_gettop(L);

	if (object_name && !b2l_is_mesh_object(L, b2l_data_idx, object_name)) {
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
					if (b2l_is_mesh_object(L, b2l_data_idx, tmp_object_name)) {
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
				if (b2l_is_mesh_object(L, b2l_data_idx, tmp_object_name)) {
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

	struct glplatform_win *win = glplatform_create_window("B2L Model viewer", &cb, NULL, 512, 512);
	if (!win) {
		fprintf(stderr, "Unable to create GL enabled window\n");
		exit(-1);
	}

	glplatform_show_window(win);

	glplatform_gl_context_t ctx = glplatform_create_context(win, 3, 3);
	if (!ctx)
		exit(-1);
	glplatform_make_current(win, ctx);

	if (!glplatform_glcore_init(3, 3)) {
		fprintf(stderr, "Failed to initialize OpenGL bindings\n");
		exit(-1);
	}
	if (!GLPLATFORM_GL_ARB_buffer_storage) {
		fprintf(stderr, "Missing GL extension: GL_ARB_buffer_storage\n");
		exit(-1);
	}
	if (!GLPLATFORM_GL_ARB_vertex_attrib_binding) {
		fprintf(stderr, "Missing GL extension: GL_ARB_vertex_attrib_binding\n");
		exit(-1);
	}
	printf("OpenGL version %s\n", glGetString(GL_VERSION));

	if (!b2l_materials_gl_setup(L, b2l_file_name, materials_idx)) {
		fprintf(stderr, "Failed to initialize GL state for B2L file\n");
		exit(-1);
	}

	while (glplatform_process_events()) {
		glViewport(0, 0, win->width, win->height);
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		struct math3d_mat4 view;
		struct math3d_mat4 model;
		struct math3d_mat4 proj;
		struct math3d_quaternion next;

		math3d_quaternion_mul(&q_delta, &q_cur, &next);
		math3d_quaternion_to_mat4(&next, &view);
		view.v[3][3] = 1;
		math3d_mat4_identity(&model);
		model.v[3][0] = g_offset.v[0] + g_offset_next.v[0];
		model.v[3][1] = g_offset.v[1] + g_offset_next.v[1];
		model.v[3][2] = g_offset.v[2] + g_offset_next.v[2];

		float zoom = exp(g_log_zoom);
		float zr = 100;
		math3d_mat4_zero(&proj);
		proj.v[0][0] = 1.0/zoom;
		proj.v[1][1] = 1.0*win->width/(zoom*win->height);
		proj.v[2][2] = 1.0/zr;
		proj.v[3][3] = 1.0;

		render_mesh(L, b2l_data_idx, materials_idx, blob,
				scene_name,
				object_name,
				frame,
				&model,
				&view,
				&proj);
		
		GLenum err = glGetError();
		if (err)
			printf("render_scene GL error: %d\n", err);
		glplatform_swap_buffers(win);
		lua_gc(L, LUA_GCCOLLECT, 0);
		glplatform_get_events(true);
	}
	return 0;
}
