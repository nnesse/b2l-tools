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
#include "glsl.tab.h"
#include "glsl_common.h"

#include "lex.glsl.h"
#undef yytext_ptr
#include "lex.meta.h"

#include "geometry.h"
#include "program.h"

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
	uint8_t *blob;
	size_t blob_size;
	bool initialized;
	bool recompile_shaders;
	bool program_valid;
	bool blob_updated;

	struct program program;

	GLuint vao;
	GLuint vbo;
	GLint groups_index;
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

int insert_shader_uniforms(lua_State *L, int text_idx, int uniform_table_idx)
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
		return -1;
	}
	d = g_decls;
	while (d) {
		if (d->gen.code == DECLARATION_NODE) {
			bool uniform = false;
			const char *type_string = "";
			int type_code;
			if (d->type) {
				struct generic_list *gl = (struct generic_list *)d->type->qualifiers;
				while (gl != NULL) {
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
		d = d->next;
	}
	return 0;
}

//
// Strip text between @ tokens from shader text
//
int filter_shader_text(lua_State *L)
{
	const char *temp = lua_tostring(L, -1);
	int sz = strlen(temp);
	char *text = malloc(sz + 2);
	strcpy(text, temp);
	text[sz + 1] = 0;
	meta_scan_buffer(text, sz + 2);
	int filtered_sz = 0;
	while (metalex()) {
		filtered_sz += strlen(metalval);
	}
	metalex_destroy();

	char *out_text = malloc(filtered_sz + 1);
	char *c = out_text;
	meta_scan_buffer(text, sz + 2);
	while (metalex()) {
		int s = strlen(metalval);
		memcpy(c, metalval, s);
		c += s;
	}
	*c = 0;
	metalex_destroy();
	free(text);
	lua_pushstring(L, out_text);
	free(out_text);
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

static bool recompile_shaders()
{
	program_compile(&g_gl_state.program);

	GLuint program = g_gl_state.program.program;
	glBindAttribLocation(program, ATTRIBUTE_VERTEX, "vertex");
	glBindAttribLocation(program, ATTRIBUTE_NORMAL, "normal");
	glBindAttribLocation(program, ATTRIBUTE_UV, "uv");
	glBindAttribLocation(program, ATTRIBUTE_TANGENT, "tangent");
	glBindAttribLocation(program, ATTRIBUTE_WEIGHT0, "weight[0]");
	glBindAttribLocation(program, ATTRIBUTE_WEIGHT1, "weight[1]");
	glBindAttribLocation(program, ATTRIBUTE_WEIGHT2, "weight[2]");
	glBindAttribLocation(program, ATTRIBUTE_WEIGHT3, "weight[3]");
	glBindAttribLocation(program, ATTRIBUTE_WEIGHT4, "weight[4]");
	glBindAttribLocation(program, ATTRIBUTE_WEIGHT5, "weight[5]");

	program_link(&g_gl_state.program);

	g_gl_state.groups_index	= glGetUniformLocation(program, "groups");
	return true;
}

static void init_gl_state()
{
	printf("OpenGL version %s\n", glGetString(GL_VERSION));
	glGenVertexArrays(1, &g_gl_state.vao);
	glBindVertexArray(g_gl_state.vao);
	glGenTextures(MAX_TEXTURE_UNITS, g_texture_names);

	program_init(&g_gl_state.program);

	glGenBuffers(1, &g_gl_state.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, g_gl_state.vbo);

	g_gl_state.initialized = true;
}

int mesh_gc(lua_State *L)
{
	struct geometry *g = lua_touserdata(L, -1);
	if (g)
		delete_geometry(g);
	return 0;
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

	lua_getglobal(L, "b2l_data"); //1
	if (!lua_istable(L, -1)) {
		lua_pop(L, 1);
		goto end;
	}
	int b2l_data_idx = lua_gettop(L);
	lua_getfield(L, b2l_data_idx, "objects");
	lua_getglobal(L, "current_object");
	if (!lua_isstring(L, -1)) {
		lua_pop(L, 3);
		goto end;
	}
	const char *current_object = lua_tostring(L, -1);
	lua_getfield(L, -2, current_object);
	if (lua_isnil(L, -1)) {
		lua_pop(L, 4);
		goto end;
	}
	int object_idx = lua_gettop(L);

	lua_getfield(L, object_idx, "type");
	if (strcmp(lua_tostring(L, -1), "MESH")) {
		lua_pop(L, 5);
		goto end;
	}
	lua_getfield(L, object_idx, "data");
	lua_getfield(L, b2l_data_idx, "meshes");
	lua_getfield(L, -1, lua_tostring(L, -2));

	if (lua_isnil(L, -1)) {
		goto end;
	}

	if (!g_gl_state.initialized)
		init_gl_state();

	lua_getglobal(L, "active_material");
	lua_getfield(L, -1, "shaders");
	lua_getfield(L, -1, "vs_text");
	lua_getfield(L, -2, "fs_text");
	const char *vs_text = lua_tostring(L, -2);
	const char *fs_text = lua_tostring(L, -1);

	if (strcmp(g_gl_state.program.vertex_text, vs_text) || strcmp(g_gl_state.program.fragment_text, fs_text)) {
		g_gl_state.program.vertex_text = strdup(vs_text);
		g_gl_state.program.fragment_text = strdup(fs_text);
		g_gl_state.recompile_shaders = true;
	}
	lua_pop(L, 4);

	if (g_gl_state.recompile_shaders)
		g_gl_state.program_valid = recompile_shaders();

	if (!g_gl_state.initialized || !g_gl_state.program_valid) {
		goto end;
	}

	int mesh_idx = lua_gettop(L);

	lua_getfield(L, mesh_idx, "geometry");
	struct geometry *g = (struct geometry *)lua_touserdata(L, -1);
	if (!g) {
		lua_pop(L, 1);

		lua_getfield(L, mesh_idx, "submeshes");
		lua_len(L, -1);
		int num_submesh = lua_tointeger(L, -1);
		lua_pop(L, 2);

		size_t geometry_size = offsetof(struct geometry, submesh[num_submesh]);
		g = (struct geometry *)lua_newuserdata(L, geometry_size);
		memset(g, 0, geometry_size);

		lua_newtable(L);
		lua_pushcfunction(L, mesh_gc);
		lua_setfield(L, -2, "__gc");
		lua_setmetatable(L, -2);

		lua_setfield(L, mesh_idx, "geometry");
		create_mesh_geometry(g, L, g_gl_state.blob);
	} else {
		lua_pop(L, 1);
	}

	g_gl_state.recompile_shaders = false;

	glUseProgram(g_gl_state.program.program);

	lua_getfield(L, object_idx, "vertex_groups");
	int num_vertex_groups;
	if (lua_isnil(L, -1)) {
		num_vertex_groups = 0;
	} else {
		lua_len(L, -1);
		num_vertex_groups = lua_tointeger(L, -1);
		lua_pop(L, 1);
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

	GLuint program = g_gl_state.program.program;

	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, (GLfloat *)&model);
	struct mat4 ident;
	mat4_identity(&ident);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, (GLfloat *)&view);

	float zoom = exp(g_log_zoom);
	float zr = 100;
	struct mat4 proj;
	mat4_zero(&proj);
	proj.v[0][0] = 1.0/zoom;
	proj.v[1][1] = 1.0*win->width/(zoom*win->height);
	proj.v[2][2] = 1.0/zr;
	proj.v[3][3] = 1.0;
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_FALSE, (GLfloat *)&proj);

	if (g_gl_state.groups_index >= 0 && g->type->attribute[ATTRIBUTE_WEIGHT0].size > 0) {
		static int render_count = 0;
		render_count++;
		double frame;
		int frame_start;
		int frame_end;
		lua_getglobal(L, "frame_start");
		frame_start = lua_tointeger(L, -1);
		lua_getglobal(L, "frame_end");
		frame_end = lua_tointeger(L, -1);
		lua_getglobal(L, "frame_delta");
		frame = frame_start + lua_tonumber(L, -1);
		int frame_i = floorf(frame);
		double frame_fract = frame - frame_i;

		lua_getfield(L, b2l_data_idx, "scenes");
		lua_getglobal(L, "current_scene");
		lua_getfield(L, -2, lua_tostring(L, -1));
		if (!lua_istable(L, -1)) {
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

	lua_getglobal(L, "controls");
	int controls = lua_gettop(L);
	lua_getglobal(L, "materials");
	int materials = lua_gettop(L);

	int i;
	for (i = 0; i < g->num_submesh; i++) {
		lua_getfield(L, materials, g->submesh[i].material_name);
		lua_getfield(L, -1, "params");
		lua_pushnil(L);  /* first key */
		while (lua_next(L, -2)) {
			int variable = lua_gettop(L);
			const char *variable_name = lua_tostring(L, variable - 1);
			int uniform_loc = glGetUniformLocation(program, variable_name);
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
		render_geometry(g, i);
		lua_pop(L, 1);
	}
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
	g_gl_state.program.fragment_text = NULL;
	g_gl_state.program.vertex_text = NULL;
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
		lua_gc(g_L, LUA_GCCOLLECT, 0);
	}
	return 0;
}
