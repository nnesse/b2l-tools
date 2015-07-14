#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <getopt.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#define GLB_ENABLE_GL_ARB_vertex_attrib_binding
#define GLB_ENABLE_GL_ARB_buffer_storage
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

#define USE_SLERP 1

static int set_b2l_file(lua_State *L);
static int need_redraw(lua_State *L);
static int set_shaders(lua_State *L);
static int make_path_relative(lua_State *L);
static int directory_name(lua_State *L);
static int create_glwin(lua_State *L);

luaL_Reg lua_b2l_material_editor_capi[] = {
	{ "directory_name", directory_name },
	{ "make_path_relative", make_path_relative },
	{ "set_b2l_file", set_b2l_file},
	{ "need_redraw", need_redraw},
	{ "set_shaders", set_shaders },
	{ "create_glwin", create_glwin},
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
static float g_log_zoom = 0.3;
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

static void generate_cylinder(int m, int n, GLuint *array_buffer, GLuint *index_buffer);

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

static float vec3_norm(const float *v)
{
	return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

static void vec3_cross(const float *a, const float *b, float *c)
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = -a[0] * b[2] + a[2] * b[0];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

static void lerp(const float *v1, const float *v2, float d, float *v3)
{
	int i;
	for (i = 0; i < 3; i++) {
		v3[i] = v1[i] * (1-d) + v2[i] * d;
	}
}

void vec3_normalize(float *v)
{
	int i;
	float norm = vec3_norm(v);
	if (norm > 0) {
		for (i = 0; i < 3; i++) {
			v[i] *= 1.0/norm;
		}
	}
}

float vec3_dot(const float *v1, const float *v2)
{
	int i;
	float ret = 0;
	for (i = 0; i < 3; i++) {
		ret += v1[i] * v2[i];
	}
	return ret;
}

static void spherical_lerp(float *v1, float *v2, float d, float *vout)
{
	float v1xv2[3];
	float v3[3];

	float v1_norm = vec3_norm(v1);
	float v2_norm = vec3_norm(v2);
	vec3_normalize(v1);
	vec3_normalize(v2);

	vec3_cross(v1, v2, v1xv2);

	double theta;

	float dot = vec3_dot(v1, v2);
	if (dot > 1) dot = 1;
	theta = acosf(dot);

	if (theta < 0.05) {
		lerp(v1, v2, d, vout);
		return;
	}

	double phi = d * theta;

	vec3_normalize(v1xv2);
	vec3_cross(v1xv2, v1, v3);

	int i = 0;
	float cos_phi = cos(phi);
	float sin_phi = sin(phi);
	for (i = 0; i < 3; i++) {
		vout[i] = (cos_phi * v1[i] + sin_phi * v3[i]) * (v1_norm * (1-d) + v2_norm * d);
	}
}

static void mat4_transpose(const struct mat4 *m, struct mat4 *out)
{
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			out->v[i][j] = m->v[j][i];
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

static void mat4_zero(struct mat4 *m)
{
	memset(m, 0, sizeof(*m));
}

static void mat4_identity(struct mat4 *m)
{
	mat4_zero(m);
	m->v[0][0] = 1;
	m->v[1][1] = 1;
	m->v[2][2] = 1;
	m->v[3][3] = 1;
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

static void on_resize(struct glwin *win)
{
	need_redraw(g_L);
}

static void on_destroy(struct glwin *win)
{
	//glwin_destroy_window(win);
	exit(0);
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
	if (g_win)
		redraw(g_win);
	return ret;
}

static gboolean dispatch(gpointer user_data)
{
	return event_process();
}

#include <gtk/gtk.h>

static gboolean idle(gpointer user_data)
{
	lua_getglobal(g_L, "playing_animation");
	bool animation_playing = lua_toboolean(g_L, -1);
	lua_pop(g_L, 1);
	if (animation_playing) {
		lua_getglobal(g_L, "animation_update");
		lua_call(g_L, 0, 0);
	}
	event_process();
	if (animation_playing)
		while (gtk_events_pending()) {
			gtk_main_iteration_do(false);
			lua_getglobal(g_L, "shutdown");
			bool shutdown = lua_toboolean(g_L, -1);
			lua_pop(g_L, 1);

			if (shutdown)
				exit(0);
		}

	return animation_playing;
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
	glwin_init();
	GMainContext *ctx = g_main_context_default();
	g_src = g_unix_fd_source_new(glwin_epoll_fd, G_IO_IN);
	g_source_attach(g_src, ctx);
	g_source_set_callback(g_src, dispatch, NULL, NULL);
	return 1;
}

static int create_glwin(lua_State *L)
{
	int xid = lua_tointeger(L, -1);
	g_win = glwin_create_window("B2L 3D View", &cb, 512, 512);
	if (!g_win)
		exit(-1);

	glwin_set_type(g_win, GLWIN_UTILITY);
	glwin_set_transient_for(g_win, xid);

	glwin_show_window(g_win);

	g_ctx = glwin_create_context(g_win, 3, 3);
	if (!g_ctx)
		exit(-1);
	glwin_make_current(g_win, g_ctx);
	/*
	if (!glb_glcore_init(3, 3) || !GLB_GL_ARB_vertex_attrib_binding || !GLB_GL_ARB_buffer_storage) {
		exit(-1);
	}
	*/

	need_redraw(L);

	return 0;
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
			struct generic_list *gl = (struct generic_list *)d->type->qualifiers;
			while(gl != NULL) {
				switch(gl->ent->code) {
				case UNIFORM:
					uniform = true;
					break;
				}
				gl = gl->next;
			}
			if (d->type->specifier && ((struct type_specifier *)d->type->specifier)->nonarray) {
				type_code = ((struct type_specifier *)d->type->specifier)->nonarray->code;
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
				lua_newtable(L);
				lua_pushstring(L, type_string);
				lua_setfield(L, -2, "datatype");
				if (d->tag) {
					lua_pushstring(L, d->tag->name);
					lua_setfield(L, -2, "tag");
				}
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

static void generate_cylinder(int m, int n, GLuint *array_buffer, GLuint *index_buffer)
{
	glGenBuffers(1, array_buffer);
	glGenBuffers(1, index_buffer);

	glBindBuffer(GL_ARRAY_BUFFER, *array_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *index_buffer);

	glBufferStorage(GL_ARRAY_BUFFER, sizeof(float) * m * (n + 1) * 3, NULL, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
	glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * (m * n * 3 * 2 + (m - 1) * 2 * 3), NULL, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

	uint16_t *idx = (uint16_t *)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
	float *r = (float *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

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

	glUnmapBuffer(GL_ARRAY_BUFFER);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
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
		fprintf(stderr, "Failed to initialize OpenGL bindings\n");
		exit(-1);
		return;
	}
	if (!GLB_GL_ARB_buffer_storage) {
		fprintf(stderr, "Missing GL extension: GL_ARB_buffer_storage\n");
		exit(-1);
	}
	if (!GLB_GL_ARB_vertex_attrib_binding) {
		fprintf(stderr, "Missing GL extension: GL_ARB_vertex_attrib_binding\n");
		exit(-1);
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
	if (g_gl_state.normal_index >= 0) {
		glEnableVertexAttribArray(g_gl_state.normal_index);
		glVertexAttribFormat(g_gl_state.normal_index, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexAttribBinding(g_gl_state.normal_index, NORMAL);
	}

	if (g_gl_state.uv_index >= 0) {
		glEnableVertexAttribArray(g_gl_state.uv_index);
		glVertexAttribFormat(g_gl_state.uv_index, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexAttribBinding(g_gl_state.uv_index, UV);
	}

	if (g_gl_state.pos_index >= 0) {
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
	if (num_uv_layers > 0 && g_gl_state.tangent_index >= 0) {
		glEnableVertexAttribArray(g_gl_state.tangent_index);
		glVertexAttribFormat(g_gl_state.tangent_index, 4, GL_FLOAT, GL_FALSE, 0);
		glVertexAttribBinding(g_gl_state.tangent_index, TANGENT);
	}

	struct mat4 view;
	struct mat4 model;
	struct quaternion next;
	quaternion_mul(&q_delta, &q_cur, &next);
	quaternion_to_mat4(&next, &view);
	view.v[3][3] = 1;
	mat4_identity(&model);
	model.v[3][0] = g_offset[0] + g_offset_next[0];
	model.v[3][1] = g_offset[1] + g_offset_next[1];
	model.v[3][2] = g_offset[2] + g_offset_next[2];
	glUniformMatrix4fv(glGetUniformLocation(g_gl_state.program, "model"), 1, GL_FALSE, (GLfloat *)&model);
	struct mat4 ident;
	mat4_identity(&ident);
	glUniformMatrix4fv(glGetUniformLocation(g_gl_state.program, "view"), 1, GL_FALSE, (GLfloat *)&view);

	float zoom = exp(g_log_zoom);
	float zr = 100;
	struct mat4 proj;
	mat4_zero(&proj);
	proj.v[0][0] = 1.0/zoom;
	proj.v[1][1] = 1.0*win->width/(zoom*win->height);
	proj.v[2][2] = 1.0/zr;
	proj.v[3][3] = 1.0;
	glUniformMatrix4fv(glGetUniformLocation(g_gl_state.program, "proj"), 1, GL_FALSE, (GLfloat *)&proj);

	if (g_gl_state.groups_index >= 0 && weights_per_vertex > 0) {
		static int render_count = 0;
		render_count++;
		double frame;
		int frame_start;
		int frame_end;
		lua_getglobal(L, "frame_start"); //16
		frame_start = lua_tointeger(L, -1);
		lua_getglobal(L, "frame_end"); //17
		frame_end = lua_tointeger(L, -1);
		lua_getglobal(L, "frame_delta"); //18
		frame = frame_start + lua_tonumber(L, -1);
		int frame_i = floorf(frame);
		double frame_fract = frame - frame_i;

		lua_getfield(L, -18, "scenes"); //19
		lua_getglobal(L, "current_scene"); //20
		lua_getfield(L, -2, lua_tostring(L, -1)); //21
		if (!lua_istable(L, -1)) {
			lua_pop(L, 20);
			goto end;
		}
		lua_getfield(L, -1, "objects");
		lua_getfield(L, -1, current_object);
		lua_getfield(L, -1, "vertex_group_transform_array_offset");
		int offset = lua_tointeger(L, -1);
		lua_pop(L, 9);
		int stride = sizeof(float) * 4 * 4 * num_vertex_groups;
		int i;
		for (i = 0; i < num_vertex_groups; i++) {
			struct mat4 res;
			struct mat4 M1;
			struct mat4 M2;
			struct mat4 *base = (struct mat4 *)(g_gl_state.blob + offset + (i * sizeof(float) * 4 * 4) + frame_i * stride);
			struct mat4 *next = (struct mat4 *)(g_gl_state.blob + offset + (i * sizeof(float) * 4 * 4) + (frame_i + 1) * stride);

			if (frame_i == (frame_end-1)) {
				next = (struct mat4 *)(g_gl_state.blob + offset + i * sizeof(float) * 4 * 4 + (frame_start) * stride);
			} else if (frame_fract == 0) {
				next = base;
			}


#if USE_SLERP
			struct mat4 temp;
			mat4_zero(&temp);
			temp.v[3][3] = 1;
			M1 = *base;
			M2 = *next;
			spherical_lerp(M1.v[0], M2.v[0], frame_fract, temp.v[0]);
			spherical_lerp(M1.v[1], M2.v[1], frame_fract, temp.v[1]);
			spherical_lerp(M1.v[2], M2.v[2], frame_fract, temp.v[2]);
			mat4_transpose(&temp, &res);
			float v1[3];
			float v2[3];
			v1[0] = M1.v[0][3];
			v1[1] = M1.v[1][3];
			v1[2] = M1.v[2][3];
			v2[0] = M2.v[0][3];
			v2[1] = M2.v[1][3];
			v2[2] = M2.v[2][3];
			lerp(v1, v2, frame_fract, res.v[3]);
#else
			mat4_zero(&res);
			res.v[3][3] = 1;
			mat4_transpose(base, &M1);
			mat4_transpose(next, &M2);
			lerp(M1.v[0], M2.v[0], frame_fract, res.v[0]);
			lerp(M1.v[1], M2.v[1], frame_fract, res.v[1]);
			lerp(M1.v[2], M2.v[2], frame_fract, res.v[2]);
			lerp(M1.v[3], M2.v[3], frame_fract, res.v[3]);
#endif

			glUniformMatrix4fv(g_gl_state.groups_index + i,
					1, /*num_vertex_groups, */
					GL_FALSE,
					(GLfloat *)&res);
		}
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
	lua_pushstring(L, "/lua/?.lua");
	lua_concat(L, 2);
	lua_setfield(L, -3, "path");

	lua_pushstring(L, b2l_data_dir);
	lua_pushstring(L, "/lua/lib/?.so");
	lua_concat(L, 2);
	lua_setfield(L, -3, "cpath");

	lua_pushcfunction(L, lua_message_handler);
	int msgh = lua_gettop(L);
	lua_pushstring(L, b2l_data_dir);
	lua_pushstring(L, "/lua/material_editor.lua");
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
		fprintf(stderr, "%s", lua_tostring(L, -1));
	}
	return 0;
}
