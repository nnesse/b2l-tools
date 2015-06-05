#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#define GLB_ENABLE_GL_ARB_vertex_attrib_binding
#include "glb-glcore.h"
#include "glsl.tab.h"
#include "glsl_common.h"

#include "lex.glsl.h"
#include "lex.meta.h"

extern char *metalval;

#include <gdk-pixbuf/gdk-pixbuf.h>

#include <glib.h>
#include <glib-unix.h>
#include <glwin.h>

#define MAX_TEXTURE_UNITS 8

static int set_b2l_file(lua_State *L);
static int need_redraw(lua_State *L);
static int set_shaders(lua_State *L);
static int make_path_relative(lua_State *L);
static int directory_name(lua_State *L);

luaL_Reg lua_b2l_material_editor[] = {
	{ "directory_name", directory_name },
	{ "make_path_relative", make_path_relative },
	{ "set_b2l_file", set_b2l_file},
	{ "need_redraw", need_redraw},
	{ "set_shaders", set_shaders },
	{ NULL, NULL }
};

static GLuint g_texture_names[MAX_TEXTURE_UNITS];

static glwin_context_t g_ctx;
static struct glwin *g_win;
static lua_State *g_L;
static bool g_need_redraw = true;
static GSource *g_src;
static int g_dx[3];
static int g_dy[3];
static bool g_mouse_down[3] = {false, false, false};

static void on_expose(struct glwin *win);
static void on_destroy(struct glwin *win);
static void on_mouse_button_up(struct glwin *, int, int, int);
static void on_mouse_button_down(struct glwin *, int, int, int);
static void on_mouse_move(struct glwin *, int, int);
static void on_resize(struct glwin *);
static void on_mouse_wheel(struct glwin *, int, int, int);

static void redraw(struct glwin *win);

struct quaternion {
	float x;
	float y;
	float z;
	float w;
};

struct mat4 {
	float v[4][4];
};

struct mat3 {
	float v[3][3];
};

#define NEW_STRUCT(TYPE) (struct TYPE *)malloc(sizeof(struct TYPE))

static struct quaternion q_cur = {0,0,0,1};
static struct quaternion q_delta = {0,0,0,1};
static float g_offset[3] = {0,0,0};
static float g_offset_next[3] = {0,0,0};

static void mat4_mul(const struct mat4 *m1, const struct mat4 *m2, struct mat4 *m3)
{
	int i, j, k;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			float v = 0;
			for (k = 0; k < 4; k++) {
				v += m1->v[k][j] * m2->v[i][k];
			}
			m3->v[i][j] = v;
		}
	}
}

static void mat4_mul_vec4(const struct mat4 *m, const float *v1, float *v2)
{
	int i, j;
	for (i = 0; i < 4; i++) {
		v2[i] = 0;
		for (j = 0; j < 4; j++) {
			v2[i] += m->v[j][i] * v1[j];
		}
	}
}

static void mat3_mul_vec3(const struct mat3 *m, const float *v1, float *v2)
{
	int i, j;
	for (i = 0; i < 3; i++) {
		v2[i] = 0;
		for (j = 0; j < 3; j++) {
			v2[i] += m->v[j][i] * v1[j];
		}
	}
}

static void quaternion_from_axis_angle(struct quaternion *q, float ax, float ay, float az, float angle)
{
	q->x = ax * sin(angle/2);
	q->y = ay * sin(angle/2);
	q->z = az * sin(angle/2);
	q->w = cos(angle/2);
}

static void quaternion_to_mat3(const struct quaternion *q, struct mat3 *m)
{
	m->v[0][0] = 1 - (2 * q->y * q->y)- (2 * q->z * q->z);
	m->v[0][1] = (2 * q->x * q->y) + (2 * q->z * q->w);
	m->v[0][2] = (2 * q->x * q->z) - (2 * q->y * q->w);

	m->v[1][0] = (2 * q->x * q->y) - (2 * q->z * q->w);
	m->v[1][1] = 1 - (2 * q->x * q->x)- (2 * q->z * q->z);
	m->v[1][2] = (2 * q->y * q->z) + (2 * q->x * q->w);

	m->v[2][0] = (2 * q->x * q->z) + (2 * q->y * q->w);
	m->v[2][1] = (2 * q->y * q->z) - (2 * q->x * q->w);
	m->v[2][2] = 1 - (2 * q->x * q->x) - (2 * q->y * q->y);
}

static void mat3_to_mat4(const struct quaternion *q, const struct mat3 *m1, struct mat4 *m2);

static void quaternion_to_mat4(const struct quaternion *q, struct mat4 *m)
{
	struct mat3 temp;
	quaternion_to_mat3(q, &temp);
	mat3_to_mat4(q, &temp, m);
}

static float quaternion_magnitude(const struct quaternion *q)
{
	return sqrtf(q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z);
}

static void quaternion_unit_inv(const struct quaternion *q, struct quaternion *q_inv)
{
	q_inv->w = q->w;
	q_inv->x = -q->x;
	q_inv->y = -q->y;
	q_inv->z = -q->z;
}

static void quaternion_inv(const struct quaternion *q, struct quaternion *q_inv)
{
	float mag = quaternion_magnitude(q);
	quaternion_unit_inv(q, q_inv);
	q_inv->w /= mag * mag;
	q_inv->x /= mag * mag;
	q_inv->y /= mag * mag;
	q_inv->z /= mag * mag;
}

static void mat3_to_mat4(const struct quaternion *q, const struct mat3 *m1, struct mat4 *m2)
{
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			m2->v[i][j] = m1->v[i][j];
		}
	}
	m2->v[3][0] = 0;
	m2->v[3][1] = 0;
	m2->v[3][2] = 0;
	m2->v[3][3] = 0;
	m2->v[0][3] = 0;
	m2->v[1][3] = 0;
	m2->v[2][3] = 0;
}

static void quaternion_mul(const struct quaternion *q1, const struct quaternion *q2, struct quaternion *out)
{
	out->w = (q1->w * q2->w  - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z);
	out->x = (q1->w * q2->x + q1->x * q2->w  + q1->y * q2->z - q1->z * q2->y);
	out->y = (q1->w * q2->y - q1->x * q2->z + q1->y * q2->w  + q1->z * q2->x);
	out->z = (q1->w * q2->z + q1->x * q2->y - q1->y * q2->x + q1->z * q2->w);
}

static void quaternion_mul_vec3(const struct quaternion *q, const float *v1, float *v2)
{
	struct mat3 temp;
	quaternion_to_mat3(q, &temp);
	mat3_mul_vec3(&temp, v1, v2);
}

static void quaternion_unit_inv_mul_vec3(const struct quaternion *q, const float *v1, float *v2)
{
	struct mat3 temp;
	struct quaternion q_inv;
	quaternion_unit_inv(q, &q_inv);
	quaternion_to_mat3(&q_inv, &temp);
	mat3_mul_vec3(&temp, v1, v2);
}

static void on_mouse_button_up(struct glwin *win, int button, int x, int y)
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

static void on_mouse_button_down(struct glwin *win, int button, int x, int y)
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

static void on_mouse_move(struct glwin *win, int x, int y)
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

		g_need_redraw = true;
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
		g_need_redraw = true;
	}
}

static void on_expose(struct glwin *win)
{
	need_redraw(g_L);
}

static void on_mouse_wheel(struct glwin *win, int x, int y, int direction)
{
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

static int directory_name(lua_State *L)
{
	char *x = strdup(lua_tostring(L, -1));
	char *all = x;
	char *y = NULL;
	while (*x) {
		if (*x == '/')
			y = x;
		x++;
	}
	if (y) {
		*(++y) = 0;
		lua_pushstring(L, all);
	} else {
		lua_pushstring(L, "");
	}
	free(all);
	return 1;
}

static void on_resize(struct glwin *win)
{
	need_redraw(g_L);
}

static void on_destroy(struct glwin *win)
{
	glwin_destroy_window(win);
}

struct glwin_callbacks cb;

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
	uint8_t *blob;
	size_t blob_size;
	bool initialized;
	bool recompile_shaders;
	bool program_valid;
	bool blob_updated;
	const char *fragment_shader_text;
	const char *vertex_shader_text;
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint program;
	GLuint vao;
	GLuint vbo;
	GLint normal_index;
	GLint uv_index;
	GLint pos_index;
	GLint weights_index[6];
	GLint tangent_index;
	GLint groups_index;
} g_gl_state;

static bool recompile_shaders();
static void init_gl_state();

static int event_process()
{
	glwin_get_events(false);
	bool ret = glwin_process_events();
	redraw(g_win);
	return ret;
}

static gboolean dispatch(gpointer user_data)
{
	return event_process();
}

static gboolean idle(gpointer user_data)
{
	event_process();
	return false;
}

int luaopen_b2l_material_editor(lua_State *L)
{
	lua_newtable(L);
	luaL_setfuncs(L, lua_b2l_material_editor, 0);
	g_L = L;
	cb.on_expose = on_expose;
	cb.on_destroy = on_destroy;
	cb.on_resize = on_resize;
	cb.on_mouse_button_up = on_mouse_button_up;
	cb.on_mouse_button_down = on_mouse_button_down;
	cb.on_mouse_move = on_mouse_move;
	cb.on_mouse_wheel = on_mouse_wheel;
	cb.on_resize = on_resize;
	glwin_init();
	g_win = glwin_create_window("B2L 3D View", &cb, 512, 512);
	if (!g_win)
		exit(-1);

	glwin_show_window(g_win);
	g_ctx = glwin_create_context(g_win, 3, 3);
	if (!g_ctx)
		exit(-1);
	glwin_make_current(g_win, g_ctx);
	glb_glcore_init(3, 3);
	GMainContext *ctx = g_main_context_default();
	g_src = g_unix_fd_source_new(glwin_epoll_fd, G_IO_IN);
	g_source_attach(g_src, ctx);
	g_source_set_callback(g_src, dispatch, NULL, NULL);
	return 1;
}

static int need_redraw(lua_State *L)
{
	g_need_redraw = true;
	g_idle_add(idle, NULL);
	return 0;
}

static void process_declaration(lua_State *L, int uniform_table_idx, struct declaration *d)
{
	if (d->gen.code == DECLARATION_NODE) {
		bool uniform = false;
		const char *type_string = "";
		int type_code;
		if (d->type) {
			struct generic_list *gl = d->type->qualifiers;
			while(gl != NULL) {
				switch(gl->ent->code) {
				case UNIFORM:
					uniform = true;
					break;
				}
				gl = gl->next;
			}
			if (d->type->specifier && d->type->specifier->nonarray) {
				type_code = d->type->specifier->nonarray->code;
				switch (type_code) {
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
				}
			}
		}
		if (uniform) {
			lua_getfield(L, uniform_table_idx, d->name);
			if (lua_isnil(L, -1)) {
				lua_pushstring(L, type_string);
				lua_setfield(L, uniform_table_idx, d->name);
			}
			lua_pushstring(L, d->name);
			lua_rawseti(L, uniform_table_idx, lua_rawlen(L, uniform_table_idx) + 1);
			lua_pop(L, 1);
		}
	} else if (d->gen.code == FUNCTION_NODE) {
		//printf("function %s\n", d->name);
	}
}

static char *parse_shader(lua_State *L, int text_idx, int uniform_text_idx)
{
	struct declaration *d;
	char *text;
	int sz;
	int rc;
	g_decls = NULL;
	const char *temp = lua_tostring(L, text_idx);
	sz = strlen(temp);
	text = malloc(sz + 2);
	strcpy(text, temp);
	text[sz + 1] = 0;
	glsl_scan_buffer(text, sz + 2);
	rc = glslparse();
	if (rc) {
		free(text);
		return NULL;
	}
	d = g_decls;
	while (d) {
		process_declaration(L, uniform_text_idx, d);
		d = d->next;
	}
	meta_scan_buffer(text, sz + 2);
	int filtered_sz = 0;
	while(metalex()) {
		filtered_sz += strlen(metalval);
	}
	metalex_destroy();

	char *out_text = malloc(filtered_sz + 1);
	char *c = out_text;
	meta_scan_buffer(text, sz + 2);
	while(metalex()) {
		int s = strlen(metalval);
		memcpy(c, metalval, s);
		c += s;
	}
	*c = 0;
	metalex_destroy();
	free(text);
	return out_text;
}

static int set_shaders(lua_State *L)
{
	int vertex_text_index = lua_gettop(L) - 1;
	int fragment_text_index = lua_gettop(L);
	char *vertex_text;
	char *fragment_text;
	lua_newtable(L);

	vertex_text = parse_shader(L, vertex_text_index, lua_gettop(L));
	if (!vertex_text) {
		lua_pop(L, 1);
		lua_pushnil(L);
		return 1;
	}

	fragment_text = parse_shader(L, fragment_text_index, lua_gettop(L));
	if (!fragment_text) {
		free(vertex_text);
		lua_pop(L, 1);
		lua_pushnil(L);
		return 1;
	}

	if (g_gl_state.fragment_shader_text)
		free((char *)g_gl_state.fragment_shader_text);
	if (g_gl_state.vertex_shader_text)
		free((char *)g_gl_state.vertex_shader_text);
	g_gl_state.fragment_shader_text = fragment_text;
	g_gl_state.vertex_shader_text = vertex_text;
	g_gl_state.recompile_shaders = true;
	return 1;
}

static bool recompile_shaders()
{
	glShaderSource(g_gl_state.vertex_shader, 1, &g_gl_state.vertex_shader_text, NULL);
	glShaderSource(g_gl_state.fragment_shader, 1, &g_gl_state.fragment_shader_text, NULL);

	glCompileShader(g_gl_state.vertex_shader);
	glCompileShader(g_gl_state.fragment_shader);

	char info_log[1000];
	GLint ret;

	glGetShaderiv(g_gl_state.vertex_shader, GL_COMPILE_STATUS, &ret);
	if (ret == GL_FALSE) {
		glGetShaderInfoLog(g_gl_state.vertex_shader, 1000, NULL, info_log);
		printf("Vertex shader compile failed:\n %s", info_log);
		return false;
	}

	glGetShaderiv(g_gl_state.fragment_shader, GL_COMPILE_STATUS, &ret);
	if (ret == GL_FALSE) {
		glGetShaderInfoLog(g_gl_state.fragment_shader, 1000, NULL, info_log);
		printf("Fragment shader compile failed:\n %s", info_log);
		return false;
	}

	glLinkProgram(g_gl_state.program);
	g_gl_state.normal_index = glGetAttribLocation(g_gl_state.program, "normal");
	g_gl_state.uv_index = glGetAttribLocation(g_gl_state.program, "uv");
	g_gl_state.pos_index = glGetAttribLocation(g_gl_state.program, "pos");
	g_gl_state.weights_index[0] = glGetAttribLocation(g_gl_state.program, "weights[0]");
	g_gl_state.weights_index[1] = glGetAttribLocation(g_gl_state.program, "weights[1]");
	g_gl_state.weights_index[2] = glGetAttribLocation(g_gl_state.program, "weights[2]");
	g_gl_state.weights_index[3] = glGetAttribLocation(g_gl_state.program, "weights[3]");
	g_gl_state.weights_index[4] = glGetAttribLocation(g_gl_state.program, "weights[4]");
	g_gl_state.weights_index[5] = glGetAttribLocation(g_gl_state.program, "weights[5]");
	g_gl_state.tangent_index = glGetAttribLocation(g_gl_state.program, "tangent");

	g_gl_state.groups_index	= glGetUniformLocation(g_gl_state.program, "groups");
	return true;
}

enum binding_points {
	NORMAL,
	UV,
	POS,
	WEIGHTS,
	TANGENT
};

static void init_gl_state()
{
	printf("OpenGL version %s\n", glGetString(GL_VERSION));
	glGenVertexArrays(1, &g_gl_state.vao);
	glBindVertexArray(g_gl_state.vao);
	glGenTextures(MAX_TEXTURE_UNITS, g_texture_names);
	g_gl_state.program = glCreateProgram();
	g_gl_state.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	g_gl_state.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glAttachShader(g_gl_state.program, g_gl_state.vertex_shader);
	glAttachShader(g_gl_state.program, g_gl_state.fragment_shader);
	glGenBuffers(1, &g_gl_state.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, g_gl_state.vbo);

	g_gl_state.initialized = true;
}

static void redraw(struct glwin *win)
{
	struct glwin_thread_state thread_state;
	glwin_get_thread_state(&thread_state);
	glwin_make_current(win, g_ctx);

	lua_State *L = g_L;

	static bool gl_init_attempted = false;
	static bool gl_init_result = false;

	if (!gl_init_attempted) {
		gl_init_result = glb_glcore_init(3, 3);
	}
	if (!gl_init_result) {
		printf("Failed to initialize OpenGL bindings\n");
		exit(-1);
		return;
	}

	glViewport(0, 0, win->width, win->height);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	lua_getglobal(L, "b2l_data"); //1
	if (!lua_istable(L, -1)) {
		lua_pop(L, 1);
		goto end;
	}
	lua_getfield(L, -1, "objects"); //2
	lua_getglobal(L, "current_object"); //3
	if (!lua_isstring(L, -1)) {
		lua_pop(L, 3);
		goto end;
	}
	const char *current_object = lua_tostring(L, -1);
	lua_getfield(L, -2, current_object); //4
	if (lua_isnil(L, -1)) {
		lua_pop(L, 4);
		goto end;
	}

	lua_getfield(L, -1, "type"); //5
	if(strcmp(lua_tostring(L, -1), "MESH")) {
		lua_pop(L, 5);
		goto end;
	}
	lua_getfield(L, -2, "data"); //6
	lua_getfield(L, -6, "meshes"); //7
	lua_getfield(L, -1, lua_tostring(L, -2)); //8

	if (lua_isnil(L, -1)) {
		lua_pop(L, 8);
		goto end;
	}

	if (!g_gl_state.initialized)
		init_gl_state();

	if (g_gl_state.recompile_shaders)
		g_gl_state.program_valid = recompile_shaders();

	if (!g_gl_state.initialized || !g_gl_state.program_valid) {
		lua_pop(L, 8);
		goto end;
	}

	g_gl_state.recompile_shaders = false;

	glUseProgram(g_gl_state.program);
	glBindVertexArray(g_gl_state.vao);

	if (g_gl_state.blob_updated)  {
		glBufferData(GL_ARRAY_BUFFER, g_gl_state.blob_size, g_gl_state.blob ,GL_STATIC_DRAW);
		g_gl_state.blob_updated = false;
	}

	lua_getfield(L, -1, "vertex_normal_array_offset"); //9
	int vertex_normal_array_offset = lua_tointeger(L, -1);
	lua_getfield(L, -2, "uv_array_offset"); //10
	int uv_array_offset = lua_tointeger(L, -1);

	lua_getfield(L, -3, "uv_layers"); //11
	lua_len(L, -1); //12
	int num_uv_layers = lua_tointeger(L, -1);

	int tangent_array_offset;
	if (num_uv_layers > 0) {
		lua_getfield(L, -5, "tangent_array_offset");
		tangent_array_offset = lua_tointeger(L, -1);
		lua_pop(L, 1);
	}

	lua_getfield(L, -5, "vertex_co_array_offset"); //13
	int vertex_co_array_offset = lua_tointeger(L, -1);

	lua_getfield(L, -6, "weights_per_vertex"); //14
	int weights_per_vertex = lua_tointeger(L, -1);

	int weights_array_offset;
	if (weights_per_vertex > 0) {
		lua_getfield(L, -7, "weights_array_offset");
		weights_array_offset = lua_tointeger(L, -1);
		lua_pop(L, 1);
	} else {
		weights_array_offset = -1;
	}

	lua_getfield(L, -11, "vertex_groups"); //15
	int num_vertex_groups;
	if (lua_isnil(L, -1)) {
		num_vertex_groups = 0;
	} else {
		lua_len(L, -1);
		num_vertex_groups = lua_tointeger(L, -1);
		lua_pop(L, 1);
	}

	glBindVertexBuffer(NORMAL, g_gl_state.vbo, vertex_normal_array_offset, sizeof(float) * 3);
	if (num_uv_layers > 0) {
		glBindVertexBuffer(UV, g_gl_state.vbo, uv_array_offset, sizeof(float) * 2 * num_uv_layers);
		glBindVertexBuffer(TANGENT, g_gl_state.vbo, tangent_array_offset, sizeof(float) * 4);
	}
	glBindVertexBuffer(POS, g_gl_state.vbo, vertex_co_array_offset, sizeof(float) * 3);
	if (weights_per_vertex > 0)
		glBindVertexBuffer(WEIGHTS, g_gl_state.vbo, weights_array_offset, weights_per_vertex * 4);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_gl_state.vbo);
	if (g_gl_state.normal_index > 0) {
		glEnableVertexAttribArray(g_gl_state.normal_index);
		glVertexAttribFormat(g_gl_state.normal_index, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexAttribBinding(g_gl_state.normal_index, NORMAL);
	}

	if (g_gl_state.uv_index > 0) {
		glEnableVertexAttribArray(g_gl_state.uv_index);
		glVertexAttribFormat(g_gl_state.uv_index, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexAttribBinding(g_gl_state.uv_index, UV);
	}

	if (g_gl_state.pos_index > 0) {
		glEnableVertexAttribArray(g_gl_state.pos_index);
		glVertexAttribFormat(g_gl_state.pos_index, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexAttribBinding(g_gl_state.pos_index, POS);
	}
	int i = 0;
	for (i = 0; i < 6; i++) {
		if (g_gl_state.weights_index[i] >= 0 && weights_per_vertex > 0) {
			glEnableVertexAttribArray(g_gl_state.weights_index[i]);
			glVertexAttribIFormat(g_gl_state.weights_index[i], 2, GL_SHORT, 4 * i);
			glVertexAttribBinding(g_gl_state.weights_index[i], WEIGHTS);
		}
	}
	if (num_uv_layers > 0 && g_gl_state.tangent_index > 0) {
		glEnableVertexAttribArray(g_gl_state.tangent_index);
		glVertexAttribFormat(g_gl_state.tangent_index, 4, GL_FLOAT, GL_FALSE, 0);
		glVertexAttribBinding(g_gl_state.tangent_index, TANGENT);
	}

	struct mat4 M1;
	struct mat4 M2;
	struct mat4 M3;
	struct quaternion next;
	quaternion_mul(&q_delta, &q_cur, &next);
	quaternion_to_mat4(&next, &M1);
	M1.v[3][3] = 1;
	memset(&M2, 0, sizeof(M2));
	M2.v[0][0] = 1;
	M2.v[1][1] = 1;
	M2.v[2][2] = 1;
	M2.v[3][3] = 1;
	M2.v[3][0] = g_offset[0] + g_offset_next[0];
	M2.v[3][1] = g_offset[1] + g_offset_next[1];
	M2.v[3][2] = g_offset[2] + g_offset_next[2];
	mat4_mul(&M1, &M2, &M3);
	glUniformMatrix4fv(glGetUniformLocation(g_gl_state.program, "mvp"), 1, GL_FALSE, (GLfloat *)&M3);

	if (weights_per_vertex > 0) {
		static int render_count = 0;
		render_count++;
		int frame;
		lua_getglobal(L, "frame_start"); //16
		frame = lua_tointeger(L, -1);
		lua_getglobal(L, "frame_delta"); //17
		frame += lua_tointeger(L, -1);

		lua_getfield(L, -17, "scenes"); //18
		lua_getglobal(L, "current_scene"); //19
		lua_getfield(L, -2, lua_tostring(L, -1)); //20
		if (!lua_istable(L, -1)) {
			lua_pop(L, 20);
			goto end;
		}
		lua_getfield(L, -1, "objects");
		lua_getfield(L, -1, current_object);
		lua_getfield(L, -1, "vertex_group_transform_array_offset");
		int offset = lua_tointeger(L, -1);
		lua_pop(L, 8);
		offset += frame * sizeof(float) * 4 * 4 * num_vertex_groups;

		glUniformMatrix4fv(g_gl_state.groups_index,
				num_vertex_groups,
				GL_TRUE,
				(GLfloat *)(g_gl_state.blob + offset));
	}

	lua_getglobal(L, "controls"); //16
	int controls = lua_gettop(L);
	lua_getglobal(L, "materials"); //17
	int materials = lua_gettop(L);

	lua_getfield(L, -10, "index_array_offset"); //18
	int index_array_offset = lua_tointeger(L, -1);

	lua_getfield(L, -11, "submeshes"); //19
	lua_len(L, -1); //20
	int num_submeshes = lua_tointeger(L, -1);

	for (i = 0; i < num_submeshes; i++) {
		lua_rawgeti(L, -2, i + 1);
		lua_getfield(L, -1, "material_name");

		const char *material_name = lua_tostring(L, -1);

		lua_getfield(L, -2, "triangle_no");
		int triangle_no = lua_tointeger(L, -1);
		lua_getfield(L, -3, "triangle_count");
		int triangle_count = lua_tointeger(L, -1);
		lua_getfield(L, materials, material_name);
		lua_getfield(L, -1, "params");
		lua_pushnil(L);  /* first key */
		while (lua_next(L, -2)) {
			int variable = lua_gettop(L);
			const char *variable_name = lua_tostring(L, variable - 1);
			int uniform_loc = glGetUniformLocation(g_gl_state.program, variable_name);
			if (uniform_loc == -1) {
				lua_pop(L, 1);
				continue;
			}
			lua_getfield(L, variable, "value");
			int value = variable + 1;
			lua_getfield(L, variable, "datatype");
			const char *datatype = strdup(lua_tostring(L, -1));
			lua_pop(L, 1);
			if (!strcmp(datatype, "bool")) {
				int bool_value = lua_toboolean(L, value);
				glUniform1i(uniform_loc, bool_value);
			} else if (!strcmp(datatype, "vec3")) {
				lua_rawgeti(L, value, 1);
				lua_rawgeti(L, value, 2);
				lua_rawgeti(L, value, 3);
				float val[3];
				val[0] = (float)lua_tonumber(L, -3);
				val[1] = (float)lua_tonumber(L, -2);
				val[2] = (float)lua_tonumber(L, -1);
				glUniform3fv(uniform_loc, 1, val);
				lua_pop(L, 3);
			} else if (!strcmp(datatype, "float")) {
				float fval = lua_tonumber(L, value);
				glUniform1f(uniform_loc, fval);
			} else if (!strcmp(datatype, "sampler2D")) {
				lua_getfield(L, controls, variable_name);
				int control = lua_gettop(L);
				lua_getfield(L, control, "needs_upload");
				int needs_upload = lua_toboolean(L, -1);
				lua_pop(L, 1);
				if (needs_upload) {
					int texunit;
					GdkPixbuf *pbuf;
					lua_getfield(L, control, "texunit");
					texunit = lua_tointeger(L, -1) - 1;
					lua_pop(L, 1);

					lua_getfield(L, control, "pbuf");
					lua_getfield(L, -1, "_native");
					pbuf = (GdkPixbuf *)lua_touserdata(L, -1);
					lua_pop(L, 2);
					glActiveTexture(GL_TEXTURE0 + texunit);
					glBindTexture(GL_TEXTURE_2D, g_texture_names[texunit]);
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
					lua_setfield(L, control, "needs_upload");
				}
				lua_pop(L, 1);
			}
			free((void *)datatype);
			lua_pop(L, 2);
		} //while (lua_next(L, -2) != 0)
		glDrawElements(GL_TRIANGLES,
				3 * triangle_count,
				GL_UNSIGNED_SHORT,
				(void *)((int64_t)index_array_offset) + 3 * 2 * triangle_no);
		lua_pop(L, 6);
	}
	lua_pop(L, 20);
end:
	{
		GLenum err = glGetError();
		if (err)
			printf("render_scene GL error = %d\n", err);
	}
	glwin_swap_buffers(g_win);
	glwin_set_thread_state(&thread_state);
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
	g_gl_state.fragment_shader_text = NULL;
	g_gl_state.vertex_shader_text = NULL;
	g_gl_state.program_valid = false;
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

int luaopen_lgi_corelgilua51 (lua_State* L);

int main()
{
	lua_State *L = lua_newstate(l_alloc, NULL);
	luaL_openlibs(L);

	lua_getglobal(L, "package"); //1
	lua_getfield(L, -1, "preload"); //2
	lua_pushcfunction(L, luaopen_b2l_material_editor);
	lua_setfield(L, -2, "b2l_material_editor");

	lua_pushcfunction(L, luaopen_lgi_corelgilua51);
	lua_setfield(L, -2, "lgi.corelgilua51");

	lua_pushstring(L, DATA_LUA_DIR "/?.lua");
	lua_setfield(L, -3, "path");

	lua_pushstring(L, DATA_LUALIB_DIR "/?.so");
	lua_setfield(L, -3, "cpath");

	luaL_loadfile(L, DATA_DIR "/b2l_material_editor.lua");
	lua_pcall(L, 0, 0, 0);
	return 0;
}
