#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#define GLB_ENABLE_GL_ARB_vertex_attrib_binding
#include "glb-glcore.h"
#include "glsl.tab.h"
#include "glsl_common.h"

#include "glsl.yy.c"

#include <gdk-pixbuf/gdk-pixbuf.h>

#include <glib.h>
#include <glib-unix.h>
#include <glwin.h>

#define MAX_TEXTURE_UNITS 8

static GLuint g_texture_names[MAX_TEXTURE_UNITS];

static struct mesh *g_mesh;
static struct object *g_obj;
static GLXContext g_ctx;
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
		g_need_redraw = 1;
	}
	if (g_mouse_down[2] && button == 3) {
		g_offset[0] += g_offset_next[0];
		g_offset[1] += g_offset_next[1];
		g_offset[2] += g_offset_next[2];
		g_offset_next[0] = 0;
		g_offset_next[1] = 0;
		g_offset_next[2] = 0;
		g_need_redraw = 1;
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
	g_need_redraw = true;
}

static void on_mouse_wheel(struct glwin *win, int x, int y, int direction)
{
}

static void on_resize(struct glwin *win)
{
	g_need_redraw = true;
}

static void on_destroy(struct glwin *win)
{
	glwin_manager_destroy_window(win);
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

struct scene {
	uint8_t *blob;
	GLuint blob_buffer;
	size_t blob_size;
	bool initialized;
	bool recompile_shaders;
	bool program_valid;
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
};

struct mesh {
	char *name;
	struct mesh *next;
	struct mesh **pprev;
	struct scene *scene;

	int num_verticies;
	int num_triangles;
	int num_uv_layers;
	int num_vertex_groups;
	int weights_per_vertex;
	int vertex_co_array_offset;
	int uv_array_offset;
	int vertex_normal_array_offset;
	int index_array_offset;
	int weights_array_offset;
	int tangent_array_offset;
	GLuint vao;
};

struct object {
	char *name;
	struct object *next;
	struct object **pprev;
	struct scene *scene;

	int object_transform_array_offset;
	int vertex_group_transform_array_offset;
	union {
		char *str;
		struct object *ref;
	} armature_deform;
	bool is_mesh;
	int num_frames;
	int num_vertex_groups;
	struct mesh *mesh;
};

struct object *obj_hash[32];
struct mesh *mesh_hash[32];

int hash(const char *str)
{
	int ret = 1;
	while (*str) {
		ret += *str;
		ret <<= 1;
		str++;
	}
	return ret & 0x1f;
}

struct object *find_obj(const char *str)
{
	int h = hash(str);
	struct object *ent = obj_hash[h];
	while(ent && strcmp(ent->name, str)) {
		ent = ent->next;
	}
	return ent;
}

void add_obj(struct object *ent)
{
	int h = hash(ent->name);
	ent->next = obj_hash[h];
	ent->pprev = obj_hash + h;
	obj_hash[h] = ent;
}

struct mesh *find_mesh(const char *str)
{
	int h = hash(str);
	struct mesh *ent = mesh_hash[h];
	while(ent && strcmp(ent->name, str)) {
		ent = ent->next;
	}
	return ent;
}

void add_mesh(struct mesh *ent)
{
	int h = hash(ent->name);
	ent->next = mesh_hash[h];
	ent->pprev = mesh_hash + h;
	mesh_hash[h] = ent;
}

static int parse_scene(lua_State *L);
static int need_redraw(lua_State *L);
static int set_shaders(lua_State *L);

static bool recompile_shaders(struct scene *s);
static void init_scene(struct scene *s);

luaL_Reg lua_b2l_material_editor[] = {
	{ "parse_scene", parse_scene },
	{ "need_redraw", need_redraw},
	{ "set_shaders", set_shaders },
	{ NULL, NULL }
};

static int event_process()
{
	glwin_manager_get_events(false);
	bool ret = glwin_manager_process_events();
	//if (ret && g_need_redraw) {
		redraw(g_win);
	//}
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
	glwin_manager_init();
	g_win = glwin_manager_create_window("B2L 3D View", &cb, 512, 512);
	if (!g_win)
		exit(-1);

	glwin_show_window(g_win);
	g_ctx = glwin_create_context(g_win, 3, 3);
	if (!g_ctx)
		exit(-1);
	glwin_manager_make_current(g_win, g_ctx);
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
	YY_BUFFER_STATE bs;
	g_decls = NULL;
	const char *temp = lua_tostring(L, text_idx);
	sz = strlen(temp);
	text = malloc(sz + 2);
	strcpy(text, temp);
	text[sz + 1] = 0;
	bs = yy_scan_buffer(text, sz + 2);
	yy_switch_to_buffer(bs);
	rc = yyparse();
	if (rc) {
		free(text);
		return NULL;
	}
	d = g_decls;
	while (d) {
		process_declaration(L, uniform_text_idx, d);
		d = d->next;
	}
	return text;
}

static int set_shaders(lua_State *L)
{
	int fragment_text_index = lua_gettop(L);
	int vertex_text_index = lua_gettop(L) - 1;
	struct scene *s = (struct scene *)lua_touserdata(L, -3);
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

	if (s->fragment_shader_text)
		free((char *)s->fragment_shader_text);
	if (s->vertex_shader_text)
		free((char *)s->vertex_shader_text);
	s->fragment_shader_text = fragment_text;
	s->vertex_shader_text = vertex_text;
	s->recompile_shaders = true;
	return 1;
}

static bool recompile_shaders(struct scene *s)
{
	glShaderSource(s->vertex_shader, 1, &s->vertex_shader_text, NULL);
	glShaderSource(s->fragment_shader, 1, &s->fragment_shader_text, NULL);

	glCompileShader(s->vertex_shader);
	glCompileShader(s->fragment_shader);

	char info_log[1000];
	GLint ret;

	glGetShaderiv(s->vertex_shader, GL_COMPILE_STATUS, &ret);
	if (ret == GL_FALSE) {
		glGetShaderInfoLog(s->vertex_shader, 1000, NULL, info_log);
		printf("Vertex shader compile failed:\n %s", info_log);
		return false;
	}

	glGetShaderiv(s->fragment_shader, GL_COMPILE_STATUS, &ret);
	if (ret == GL_FALSE) {
		glGetShaderInfoLog(s->fragment_shader, 1000, NULL, info_log);
		printf("Fragment shader compile failed:\n %s", info_log);
		return false;
	}

	glLinkProgram(s->program);
	s->normal_index = glGetAttribLocation(s->program, "normal");
	s->uv_index = glGetAttribLocation(s->program, "uv");
	s->pos_index = glGetAttribLocation(s->program, "pos");
	s->weights_index[0] = glGetAttribLocation(s->program, "weights[0]");
	s->weights_index[1] = glGetAttribLocation(s->program, "weights[1]");
	s->weights_index[2] = glGetAttribLocation(s->program, "weights[2]");
	s->weights_index[3] = glGetAttribLocation(s->program, "weights[3]");
	s->weights_index[4] = glGetAttribLocation(s->program, "weights[4]");
	s->weights_index[5] = glGetAttribLocation(s->program, "weights[5]");
	s->tangent_index = glGetAttribLocation(s->program, "tangent");

	s->groups_index	= glGetUniformLocation(s->program, "groups");
	return true;
}

enum binding_points {
	NORMAL,
	UV,
	POS,
	WEIGHTS,
	TANGENT
};

static void init_scene(struct scene *s)
{
	printf("OpenGL version %s\n", glGetString(GL_VERSION));
	glGenVertexArrays(1, &s->vao);
	glBindVertexArray(s->vao);
	glGenTextures(MAX_TEXTURE_UNITS, g_texture_names);
	s->program = glCreateProgram();
	s->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	s->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glAttachShader(s->program, s->vertex_shader);
	glAttachShader(s->program, s->fragment_shader);

	glGenBuffers(1, &s->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, s->vbo);
	glBufferData(GL_ARRAY_BUFFER, s->blob_size, s->blob, GL_STATIC_DRAW);

	s->initialized = true;
}

static void setup_vao(struct scene *s, struct mesh *m)
{
	glBindVertexBuffer(NORMAL, s->vbo, m->vertex_normal_array_offset, sizeof(float) * 3);
	if (m->num_uv_layers > 0) {
		glBindVertexBuffer(UV, s->vbo, m->uv_array_offset, sizeof(float) * 2 * m->num_uv_layers);
		glBindVertexBuffer(TANGENT, s->vbo, m->tangent_array_offset, sizeof(float) * 4);
	}
	glBindVertexBuffer(POS, s->vbo, m->vertex_co_array_offset, sizeof(float) * 3);
	if (m->weights_per_vertex > 0)
		glBindVertexBuffer(WEIGHTS, s->vbo, m->weights_array_offset, m->weights_per_vertex * 4);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s->vbo);
	if (s->normal_index > 0) {
		glEnableVertexAttribArray(s->normal_index);
		glVertexAttribFormat(s->normal_index, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexAttribBinding(s->normal_index, NORMAL);
	}

	if (s->uv_index > 0) {
		glEnableVertexAttribArray(s->uv_index);
		glVertexAttribFormat(s->uv_index, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexAttribBinding(s->uv_index, UV);
	}

	if (s->pos_index > 0) {
		glEnableVertexAttribArray(s->pos_index);
		glVertexAttribFormat(s->pos_index, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexAttribBinding(s->pos_index, POS);
	}
	int i = 0;
	for (i = 0; i < 6; i++) {
		if (s->weights_index[i] >= 0 && m->weights_per_vertex > 0) {
			glEnableVertexAttribArray(s->weights_index[i]);
			glVertexAttribIFormat(s->weights_index[i], 2, GL_SHORT, 4 * i);
			glVertexAttribBinding(s->weights_index[i], WEIGHTS);
		}
	}
	if (m->num_uv_layers > 0 && s->tangent_index > 0) {
		glEnableVertexAttribArray(s->tangent_index);
		glVertexAttribFormat(s->tangent_index, 4, GL_FLOAT, GL_FALSE, 0);
		glVertexAttribBinding(s->tangent_index, TANGENT);
	}
}

static void redraw(struct glwin *win)
{
	GLXDrawable write_draw = glXGetCurrentDrawable();
	GLXDrawable read_draw = glXGetCurrentDrawable();
	Display *display = glXGetCurrentDisplay();
	GLXContext prev_ctx = glXGetCurrentContext();
	glwin_manager_make_current(win, g_ctx);

	lua_State *L = g_L;
	struct mesh *m = g_mesh;
	struct scene *s;

	static bool gl_init_attempted = false;
	static bool gl_init_result = false;

	if (!gl_init_attempted) {
		gl_init_result = glb_glcore_init(3, 3);
	}
	if (!gl_init_result) {
		printf("init failed\n");
		return;
	}

	glViewport(0, 0, win->width, win->height);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	if (!m)
		goto end;

	s = m->scene;
	if (!s->initialized)
		init_scene(s);

	if (s->recompile_shaders) {
		s->program_valid = recompile_shaders(s);
	}

	if (!s || !s->initialized || !s->program_valid)
		return;

	if (m->vao == 0) {
		glGenVertexArrays(1, &m->vao);
		glBindVertexArray(m->vao);
		setup_vao(s, m);
	} else {
		glBindVertexArray(m->vao);
		if (s->recompile_shaders)
			setup_vao(s, m);
	}
	s->recompile_shaders = false;

	glUseProgram(s->program);
	lua_getglobal(L, "controls");
	lua_pushnil(L);  /* first key */
	while (lua_next(L, -2) != 0) {
		int variable = lua_gettop(L);
		int uniform_loc = glGetUniformLocation(s->program, lua_tostring(L, variable - 1));
		lua_getfield(L, variable, "value");
		int value = variable + 1;
		lua_getfield(L, variable, "datatype");
		const char *datatype = strdup(lua_tostring(L, -1));
		lua_pop(L, 1);
		if (!strcmp(datatype, "bool")) {
			glUniform1i(uniform_loc, lua_toboolean(L, value));
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
			lua_getfield(L, variable, "needs_upload");
			int needs_upload = lua_toboolean(L, -1);
			lua_pop(L, 1);
			if (needs_upload) {
				int texunit;
				GdkPixbuf *pbuf;
				lua_getfield(L, variable, "texunit");
				texunit = lua_tointeger(L, -1) - 1;
				lua_pop(L, 1);

				lua_getfield(L, value, "_native");
				pbuf = (GdkPixbuf *)lua_touserdata(L, -1);
				lua_pop(L, 1);
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
				lua_setfield(L, variable, "needs_upload");
			}
		}
		free((void *)datatype);
		lua_pop(L, 2);
	}
	lua_pop(L, 1);
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
	glUniformMatrix4fv(glGetUniformLocation(s->program, "mvp"), 1, GL_FALSE, (GLfloat *)&M3);

	if (g_mesh->weights_per_vertex > 0) {
		static int render_count = 0;
		render_count++;
		int frame = (render_count/3) % g_obj->num_frames;
		int offset = g_obj->vertex_group_transform_array_offset;
		offset += frame * sizeof(float) * 4 * 4 * g_obj->num_vertex_groups;

		glUniformMatrix4fv(s->groups_index,
				g_obj->num_vertex_groups,
				GL_TRUE,
				(GLfloat *)(s->blob + offset));
	}

	glDrawElements(GL_TRIANGLES, 3 * m->num_triangles, GL_UNSIGNED_SHORT, (void *)((int64_t)m->index_array_offset));
	{
		GLenum err = glGetError();
		if (err)
			printf("render_scene GL error = %d\n", err);
	}
end:
	glwin_swap_buffers(g_win);
	glXMakeContextCurrent(display, write_draw, read_draw, prev_ctx);
	g_need_redraw = false;
	return;
}

static int parse_scene(lua_State *L)
{
	int scene_index = lua_gettop(L) - 1;
	int filename_index = lua_gettop(L);

	size_t blob_size;
	uint8_t *blob = get_file_buffer(lua_tostring(L, filename_index), &blob_size);
	if (blob == NULL) {
		printf("failed to load blob file %s\n",lua_tostring(L, filename_index));
		return -1;
	}

	struct scene *s = (struct scene *)malloc(sizeof(struct scene));
	s->blob = blob;
	s->blob_size = blob_size;
	s->initialized = false;
	s->blob_buffer = 0;
	s->fragment_shader_text = NULL;
	s->vertex_shader_text = NULL;
	s->program_valid = false;
	s->recompile_shaders = false;

	lua_pushlightuserdata(L, s);
	lua_setfield(L, scene_index, "userdata");

	lua_getfield(L, scene_index, "meshes");
	int meshes_index = lua_gettop(L);
	lua_pushnil(L);
	while (lua_next(L, meshes_index)) {
		struct mesh *m = NEW_STRUCT(mesh);
		g_mesh = m;
		m->name = strdup(lua_tostring(L, -2));
		m->scene = s;
		m->vao = 0;

		int mesh_index = lua_gettop(L);

		lua_getfield(L, mesh_index, "num_verticies");
		m->num_verticies = lua_tointeger(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, mesh_index, "num_triangles");
		m->num_triangles = lua_tointeger(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, mesh_index, "uv_layers");
		lua_len(L, -1);
		m->num_uv_layers = lua_tointeger(L, -1);
		lua_pop(L, 2);

		lua_getfield(L, mesh_index, "weights_per_vertex");
		m->weights_per_vertex = lua_tointeger(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, mesh_index, "index_array_offset");
		m->index_array_offset = lua_tointeger(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, mesh_index, "vertex_co_array_offset");
		m->vertex_co_array_offset = lua_tointeger(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, mesh_index, "uv_array_offset");
		m->uv_array_offset = lua_tointeger(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, mesh_index, "vertex_normal_array_offset");
		m->vertex_normal_array_offset = lua_tointeger(L, -1);
		lua_pop(L, 1);

		if (m->weights_per_vertex > 0) {
			lua_getfield(L, mesh_index, "weights_array_offset");
			m->weights_array_offset = lua_tointeger(L, -1);
			lua_pop(L, 1);
		} else {
			m->weights_array_offset = -1;
		}

		if (m->num_uv_layers > 0) {
			lua_getfield(L, mesh_index, "tangent_array_offset");
			m->tangent_array_offset = lua_tointeger(L, -1);
			lua_pop(L, 1);
		}

		add_mesh(m);

		lua_pushlightuserdata(L, m);
		lua_setfield(L, mesh_index, "userdata");

		lua_pop(L, 1); /* Pop value */
	}
	lua_pop(L, 2);

	lua_getfield(L, scene_index, "scene");
	lua_getfield(L, -1, "objects");
	int objects_index = lua_gettop(L);
	lua_pushnil(L);
	while (lua_next(L, objects_index)) {
		struct object *obj =  NEW_STRUCT(object);
		int obj_index = lua_gettop(L);
		bool is_mesh = 0;
		obj->scene = s;

		obj->name = strdup(lua_tostring(L, -2));
		lua_getfield(L, obj_index, "type");
		is_mesh = !strcmp(lua_tostring(L, -1),"MESH");
		lua_pop(L, 1);

		lua_getfield(L, obj_index, "num_frames");
		obj->num_frames = lua_tointeger(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, obj_index, "armature_deform");
		if (lua_isstring(L, -1)) {
			obj->armature_deform.str = strdup(lua_tostring(L, -1));
		} else {
			obj->armature_deform.str = NULL;
		}
		lua_pop(L, 1);

		if (is_mesh) {
			lua_getfield(L, obj_index, "data");
			obj->mesh = find_mesh(lua_tostring(L, -1));
			lua_pop(L, 1);
			if (obj->mesh == g_mesh) {
				g_obj = obj;
			}
		} else {
			obj->mesh = NULL;
		}

		lua_getfield(L, obj_index, "object_transform_array_offset");
		obj->object_transform_array_offset = lua_tointeger(L, -1);
		lua_pop(L, 1);

		lua_getfield(L, obj_index, "vertex_groups");
		if (lua_isnil(L, -1)) {
			obj->num_vertex_groups = 0;
		} else {
			lua_len(L, -1);
			obj->num_vertex_groups = lua_tointeger(L, -1);
			lua_pop(L, 1);
		}
		lua_pop(L, 1);

		lua_getfield(L, obj_index, "vertex_group_transform_array_offset");
		if (lua_isnumber(L, -1)) {
			obj->vertex_group_transform_array_offset = lua_tointeger(L, -1);
		} else {
			obj->vertex_group_transform_array_offset = -1;
		}
		lua_pop(L, 1);

		lua_pushlightuserdata(L, obj);
		lua_setfield(L, obj_index, "userdata");

		lua_pop(L, 1);
	}
	lua_pop(L, 3);
	return 0;
}
