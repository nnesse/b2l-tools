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

static int set_b2l_file(lua_State *L);
static int need_redraw(lua_State *L);
static int get_shader_uniforms(lua_State *L);
static int filter_shader_text(lua_State *L);
static int make_path_relative(lua_State *L);
static int directory_name(lua_State *L);
static int create_glwin(lua_State *L);

luaL_Reg lua_b2l_material_editor_capi[] = {
	{ "directory_name", directory_name },
	{ "make_path_relative", make_path_relative },
	{ "set_b2l_file", set_b2l_file},
	{ "need_redraw", need_redraw},
	{ "get_shader_uniforms", get_shader_uniforms},
	{ "filter_shader_text", filter_shader_text},
	{ "create_glwin", create_glwin},
	{ NULL, NULL }
};

static GLuint g_texture_names[MAX_TEXTURE_UNITS];

static glplatform_gl_context_t g_ctx;
static struct glplatform_win *g_win;
static lua_State *g_L;
static bool g_need_redraw = true;
static GSource *g_src;
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

static void redraw(struct glplatform_win *win);

struct lua_program {
	struct program program;
};

int program_gc(lua_State *L)
{
	struct program *p = lua_touserdata(L, -1);
	if (p)
		program_destroy(p);
	return 0;
}

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
		need_redraw(g_L);
	}
	if (g_mouse_down[2] && button == 3) {
		g_offset[0] += g_offset_next[0];
		g_offset[1] += g_offset_next[1];
		g_offset[2] += g_offset_next[2];
		g_offset_next[0] = 0;
		g_offset_next[1] = 0;
		g_offset_next[2] = 0;
		need_redraw(g_L);
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

static void print_quaternion(struct quaternion *q)
{
	printf("%f %f %f %f\n", q->x, q->y, q->z, q->w);
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
		need_redraw(g_L);
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
		need_redraw(g_L);
	}
}

static void on_expose(struct glplatform_win *win)
{
	need_redraw(g_L);
}

static void on_mouse_wheel(struct glplatform_win *win, int x, int y, int direction)
{
	g_log_zoom  += direction * 0.1;
	need_redraw(g_L);
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
	need_redraw(g_L);
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
	*size = ftell(f);
	fseek(f, 0, SEEK_SET);
	uint8_t *ret = (uint8_t *)malloc(*size);
	if (fread(ret, *size, 1, f) != 1) {
		free(ret);
		ret = NULL;
	}
	fclose(f);
	return ret;
}

struct gl_state {
	const uint8_t *blob;
	size_t blob_size;
	bool initialized;
	bool blob_updated;
	GLuint vao;
} g_gl_state;

static bool recompile_shaders();
static void init_gl_state();

static gboolean dispatch(gpointer user_data)
{
	glplatform_get_events(false);
	return glplatform_process_events();
}

int luaopen_material_editor_capi(lua_State *L)
{
	lua_newtable(L);
	luaL_setfuncs(L, lua_b2l_material_editor_capi, 0);
	g_L = L;
	cb.on_expose = on_expose;
	cb.on_destroy = on_destroy;
	cb.on_resize = on_resize;
	cb.on_mouse_button_up = on_mouse_button_up;
	cb.on_mouse_button_down = on_mouse_button_down;
	cb.on_mouse_move = on_mouse_move;
	cb.on_mouse_wheel = on_mouse_wheel;
	cb.on_resize = on_resize;
	glplatform_init();
	GMainContext *ctx = g_main_context_default();
	g_src = g_unix_fd_source_new(glplatform_epoll_fd, G_IO_IN);
	g_source_attach(g_src, ctx);
	g_source_set_callback(g_src, dispatch, NULL, NULL);
	return 1;
}

static int create_glwin(lua_State *L)
{
	int xid = lua_tointeger(L, -1);
	g_win = glplatform_create_window("B2L 3D View", &cb, NULL, 512, 512);
	if (!g_win)
		exit(-1);

	glplatform_set_win_type(g_win, GLWIN_UTILITY);
	glplatform_set_win_transient_for(g_win, xid);

	glplatform_show_window(g_win);

	g_ctx = glplatform_create_context(g_win, 3, 3);
	if (!g_ctx)
		exit(-1);
	glplatform_make_current(g_win, g_ctx);

	need_redraw(L);

	return 0;
}

static int need_redraw(lua_State *L)
{
	g_need_redraw = true;
	return 0;
}

struct insert_shader_uniforms_state {
	const char *tag;
	const char *name;
	int type_code;
	bool uniform;
	lua_State *L;
	int uniform_table_idx;
};

static void insert_shader_uniforms_enter(struct glsl_ast_walk_data *data, struct glsl_node *n, intptr_t state_)
{
	int i;
	struct insert_shader_uniforms_state *state = (struct insert_shader_uniforms_state *) state_;
	switch(n->code) {
	case TRANSLATION_UNIT:
	case DECLARATION_STATEMENT_LIST:
		for (i = n->child_count - 1; i >= 0; i--) {
			glsl_ast_walk_push_node(data, n->children[i]); //DECLARATION_STATEMENT
		}
		break;
	case TYPE_QUALIFIER_LIST:
		for (i = 0; i < n->child_count; i++) {
			if (n->children[i]->code == UNIFORM) {
				state->uniform = true;
			}
		}
		break;
	case DECLARATION:
		glsl_ast_walk_push_node(data, n->children[0]); //declaration
		break;
	case SECTION_STATEMENT:
		state->tag = n->children[0]->data.str; //IDENTIFIER
		glsl_ast_walk_push_node(data, n->children[1]);
		break;
	case SINGLE_DECLARATION:
		state->name = n->children[1]->data.str; //IDENTIFIER
		glsl_ast_walk_push_node(data, n->children[0]);
		break;
	case FULLY_SPECIFIED_TYPE:
		glsl_ast_walk_push_node(data, n->children[1]); //TYPE_SPECIFIER
		glsl_ast_walk_push_node(data, n->children[0]); //TYPE_QUALIFIER_LIST
		break;
	case TYPE_SPECIFIER:
		state->type_code = n->children[0]->code; //type_specifier_nonarray
		break;
	}
}

static void insert_shader_uniforms_exit(struct glsl_ast_walk_data *data, struct glsl_node *n, intptr_t state_)
{
	struct insert_shader_uniforms_state *state = (struct insert_shader_uniforms_state *) state_;

	switch (n->code) {
	case SECTION_STATEMENT:
		state->tag = NULL;
		break;
	case DECLARATION: {
		const char *type_string;
		switch (state->type_code) {
		case FLOAT:
			type_string = "float";
			break;
		case VEC3:
			type_string = "vec3";
			break;
		case MAT4:
			type_string = "mat4";
			break;
		case BOOL:
			type_string = "bool";
			break;
		case SAMPLER2D:
			type_string = "sampler2D";
			break;
		default:
			type_string = NULL;
		}
		if (state->uniform && type_string && state->name) {
			lua_getfield(state->L, state->uniform_table_idx, state->name);
			if (lua_isnil(state->L, -1)) {
				lua_newtable(state->L);
				lua_pushstring(state->L, type_string);
				lua_setfield(state->L, -2, "datatype");
				if (state->tag) {
					lua_pushstring(state->L, state->tag);
					lua_setfield(state->L, -2, "tag");
				}
				lua_setfield(state->L, state->uniform_table_idx, state->name);
			}
			lua_pushstring(state->L, state->name);
			lua_rawseti(state->L, state->uniform_table_idx, lua_rawlen(state->L, state->uniform_table_idx) + 1);
			lua_pop(state->L, 1);
		}
		state->uniform = false;
		state->type_code = -1;
		state->name = NULL;
	} break;
	}
}

int insert_shader_uniforms(lua_State *L, int text_idx, int uniform_table_idx)
{
	const char *temp = lua_tostring(L, text_idx);
	struct glsl_parse_context context;

	glsl_parse_context_init(&context);

	glsl_parse_string(&context, temp);

	struct insert_shader_uniforms_state lstate;

	//Data we need during traversal
	lstate.L = L;
	lstate.uniform_table_idx = uniform_table_idx;
	lstate.type_code = -1;
	lstate.uniform = false;
	lstate.name = NULL;
	lstate.tag = NULL;

	struct glsl_ast_walk_data wd;
	glsl_ast_walk_init(&wd);
	glsl_ast_walk_push_node(&wd, context.root);
	glsl_ast_walk(&wd, (intptr_t)&lstate, insert_shader_uniforms_enter, insert_shader_uniforms_exit);

	glsl_parse_context_destroy(&context);
	return 0;
}

//
// Strip meta-data from shader text
//

int filter_shader_text(lua_State *L)
{
	const char *input = lua_tostring(L, -1);
	char *output;
	struct glsl_parse_context context;
	glsl_parse_context_init(&context);
	glsl_parse_string(&context, input);
	output = glsl_ast_generate_glsl(context.root);
	glsl_parse_context_destroy(&context);
	lua_pushstring(L, "#version 330\n"); //TODO: we need to grab the actual text for this
	lua_pushstring(L, output);
	lua_concat(L, 2);
	//glsl_ast_print(context.root, 0);
	//printf("%s\n", output);
	free(output);
	return 1;
}

static int get_shader_uniforms(lua_State *L)
{
	int vertex_text_index = lua_gettop(L) - 1;
	int fragment_text_index = lua_gettop(L);
	lua_newtable(L);

	if (insert_shader_uniforms(L, vertex_text_index, lua_gettop(L))) {
		lua_pop(L, 1);
		lua_pushnil(L);
		return 1;
	}

	if (insert_shader_uniforms(L, fragment_text_index, lua_gettop(L))) {
		lua_pop(L, 1);
		lua_pushnil(L);
		return 1;
	}
	return 1;
}

static void init_gl_state()
{
	printf("OpenGL version %s\n", glGetString(GL_VERSION));
	glGenVertexArrays(1, &g_gl_state.vao);
	glBindVertexArray(g_gl_state.vao);
	glGenTextures(MAX_TEXTURE_UNITS, g_texture_names);
	g_gl_state.initialized = true;
}

static void redraw(struct glplatform_win *win)
{
	struct glplatform_thread_state thread_state;
	glplatform_get_thread_state(&thread_state);
	glplatform_make_current(win, g_ctx);

	lua_State *L = g_L;

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
		init_gl_state();

	if (!g_gl_state.initialized) {
		goto end;
	}

	lua_getglobal(L, "b2l_data"); //1
	if (!lua_istable(L, -1)) {
		lua_pop(L, 1);
		goto end;
	}
	int b2l_data_idx = lua_gettop(L);
	lua_getglobal(L, "current_object");
	if (!lua_isstring(L, -1)) {
		goto end;
	}
	const char *current_object = lua_tostring(L, -1);

	double frame;
	int frame_start;

	lua_getglobal(L, "frame_start");
	frame_start = lua_tointeger(L, -1);
	lua_getglobal(L, "frame_delta");
	frame = frame_start + lua_tonumber(L, -1);

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

	lua_getglobal(L, "materials");
	int materials_idx = lua_gettop(L);

	if (lua_isnil(L, -1))
		goto end;

	lua_pushnil(L);
	while(lua_next(L, -2)) {
		int material_idx = lua_gettop(L);
		lua_getfield(L, material_idx, "program");

		//
		// Create material program object if it's missing
		//
		struct program *program = lua_touserdata(L, -1);
		if (!program) {
			program = lua_newuserdata(L, sizeof(struct program));
			program_init(program);
			int program_idx = lua_gettop(L);
			lua_newtable(L);
			lua_pushcfunction(L, program_gc);
			lua_setfield(L, -2, "__gc");
			lua_setmetatable(L, program_idx);
			lua_setfield(L, material_idx, "program");
		}

		//
		// Recompile material program if shader text has changed
		//
		lua_getfield(L, material_idx, "shaders");
		lua_getfield(L, -1, "_vs_text");
		lua_getfield(L, -2, "_fs_text");
		const char *vs_text = lua_tostring(L, -2);
		const char *fs_text = lua_tostring(L, -1);
		if ((vs_text && fs_text) && (strcmp(program->vertex_text, vs_text) || strcmp(program->fragment_text, fs_text))) {
			program->vertex_text = strdup(vs_text);
			program->fragment_text = strdup(fs_text);
			program_compile(program);
			glBindAttribLocation(program->program, ATTRIBUTE_VERTEX, "vertex");
			glBindAttribLocation(program->program, ATTRIBUTE_NORMAL, "normal");
			glBindAttribLocation(program->program, ATTRIBUTE_UV, "uv");
			glBindAttribLocation(program->program, ATTRIBUTE_TANGENT, "tangent");
			glBindAttribLocation(program->program, ATTRIBUTE_WEIGHT0, "weights[0]");
			glBindAttribLocation(program->program, ATTRIBUTE_WEIGHT1, "weights[1]");
			glBindAttribLocation(program->program, ATTRIBUTE_WEIGHT2, "weights[2]");
			glBindAttribLocation(program->program, ATTRIBUTE_WEIGHT3, "weights[3]");
			glBindAttribLocation(program->program, ATTRIBUTE_WEIGHT4, "weights[4]");
			glBindAttribLocation(program->program, ATTRIBUTE_WEIGHT5, "weights[5]");
			program_link(program);
		}
		if (!program->linked) {
			goto end;
		}

		lua_getfield(L, material_idx, "params");
		lua_pushnil(L);  /* first key */
		while (lua_next(L, -2)) {
			int texunit = 0;
			int variable_idx = lua_gettop(L);
			lua_getfield(L, variable_idx, "datatype");
			const char *datatype = lua_tostring(L, -1);
			if (!strcmp(datatype,"sampler2D")) {
				lua_getfield(L, variable_idx, "_needs_upload");
				int needs_upload = lua_toboolean(L, -1);

				GLuint texid = 0;
				if (needs_upload) {
					const char *variable_name = lua_tostring(L, variable_idx - 1);
					int uniform_loc = glGetUniformLocation(program->program, variable_name);
					GdkPixbuf *pbuf;

					//
					// Delete existing texture if there is one
					//
					lua_getfield(L, variable_idx, "_texid");
					if (lua_isnumber(L, -1)) {
						texid = lua_tointeger(L, -1);
						glDeleteTextures(1, &texid);
					}

					//
					// Upload pbuf to texture
					//
					lua_getfield(L, variable_idx, "_pbuf");
					lua_getfield(L, -1, "_native");
					pbuf = (GdkPixbuf *)lua_touserdata(L, -1);
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
					lua_pushboolean(L, 0);
					lua_setfield(L, variable_idx, "_needs_upload");
				}
				texunit++;

			}
			lua_settop(L, variable_idx - 1);
		}
		lua_settop(L, material_idx - 1);
	}

	render_mesh(L, b2l_data_idx, materials_idx, g_gl_state.blob,
			current_object, frame,
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
	g_need_redraw = false;
	return;
}

static int set_b2l_file(lua_State *L)
{
	size_t blob_size;
	uint8_t *blob = get_file_buffer(lua_tostring(L, -1), &blob_size);
	if (blob == NULL) {
		printf("failed to load blob file %s\n",lua_tostring(L, -1));
		return -1;
	}
	g_gl_state.blob = blob;
	g_gl_state.blob_size = blob_size;
	g_gl_state.blob_updated = true;
	return 0;
}

static void *l_alloc (void *ud, void *ptr, size_t osize, size_t nsize)
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

int luaopen_lgi_corelgilua (lua_State* L);

int lua_message_handler (lua_State* L)
{
	lua_pushvalue(L, -1);
	lua_pushstring(L, "\n");
	lua_backtrace_string(L);
	lua_concat(L, 3);
	return 1;
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

static void print_help(const char *program_name)
{
	printf("Usage: %s [OPTION]...\n", program_name);
	printf("\n"
	       "Options:\n"
	       "  -d,--data-dir <path>               Path to application data. Overrides B2L_DATA_DIR.\n"
	       "  -h,--help                          Print this page.\n");
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
	const char *b2l_data_dir = NULL;
	const char *b2l_file_name = NULL;

	static struct option options [] = {
		{"data-dir" , 1, 0, 'd' },
		{"help"     , 0, 0, 'h' }
	};

	while (1) {
		int option_index;
		int c = getopt_long(argc, argv, "d:h", options, &option_index);
		if (c == -1) {
			break;
		}
		switch(c) {
		case 'd':
			b2l_data_dir = optarg;
			break;
		case 'h':
			print_help(argv[0]);
			exit(0);
			break;
		}
	}
	if (!b2l_data_dir) {
		b2l_data_dir = getenv("B2L_DATA_DIR");
	}
	if (!b2l_data_dir) {
		b2l_data_dir = DATA_DIR;
	}

	if (optind < argc) {
		b2l_file_name = argv[optind];
	}

	lua_State *L = lua_newstate(l_alloc, NULL);
	luaL_openlibs(L);

	lua_atpanic(L, lua_panic_handler);

	lua_getglobal(L, "package"); //1
	lua_getfield(L, -1, "preload"); //2
	lua_pushcfunction(L, luaopen_material_editor_capi);
	lua_setfield(L, -2, "material_editor_capi");

	lua_pushcfunction(L, luaopen_lgi_corelgilua);
	lua_setfield(L, -2, "lgi.corelgilua");

	lua_pushstring(L, b2l_data_dir);
	lua_pushstring(L, "/?.lua;");
	lua_pushstring(L, b2l_data_dir);
	lua_pushstring(L, "/lgi/?.lua");
	lua_concat(L, 4);
	lua_setfield(L, -3, "path");

	lua_pushstring(L, b2l_data_dir);
	lua_pushstring(L, "/lib/?.so;");
	lua_pushstring(L, b2l_data_dir);
	lua_pushstring(L, "/lgi/lib/?.so");
	lua_concat(L, 4);
	lua_setfield(L, -3, "cpath");

	lua_pushcfunction(L, lua_message_handler);
	int msgh = lua_gettop(L);
	lua_pushstring(L, b2l_data_dir);
	lua_pushstring(L, "/material_editor.lua");
	lua_concat(L, 2);
	int err;
	err = luaL_loadfile(L, lua_tostring(L, -1));
	if (err != LUA_OK) {
		fprintf(stderr, "Error loading script: %s\n", lua_tostring(L, -1));
		return 0;
	}
	if (!b2l_file_name) {
		lua_pushnil(L);
	} else {
		lua_pushstring(L, b2l_file_name);
	}

	lua_setglobal(L, "b2l_filename");
	err = lua_pcall(L, 0, 0, msgh);
	switch (err) {
	case LUA_ERRRUN:
		fprintf(stderr, "Lua runtime error: ");
		break;
	case LUA_ERRMEM:
		fprintf(stderr, "Lua memory allocation error: ");
		break;
	case LUA_ERRERR:
		fprintf(stderr, "Lua internal error: ");
		break;
	case LUA_ERRGCMM:
		fprintf(stderr, "Lua garbage collection error: ");
		break;
	}
	if (err != LUA_OK) {
		fprintf(stderr, "%s\n", lua_tostring(L, -1));
		return -1;
	}

	bool shutdown = false;
	bool block = true;
	bool animation_playing = false;
	while (!shutdown) {
		while ((gtk_events_pending() || block) && !shutdown) {
			gtk_main_iteration_do(block);
			block = false;
			lua_getglobal(g_L, "shutdown");
			shutdown = lua_toboolean(g_L, -1);
			lua_pop(g_L, 1);
			lua_getglobal(g_L, "playing_animation");
			animation_playing = lua_toboolean(g_L, -1);
			lua_pop(g_L, 1);
		}
		if (animation_playing) {
			lua_getglobal(g_L, "animation_update");
			lua_call(g_L, 0, 0);
			g_need_redraw = true;
		}
		if (g_win && g_need_redraw) {
			redraw(g_win);
		}
		block = !animation_playing;
		if (!block) {
			glplatform_get_events(false);
			glplatform_process_events();
		}
		lua_gc(g_L, LUA_GCCOLLECT, 0);
	}
	return 0;
}
