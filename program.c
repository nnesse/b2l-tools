#include "program.h"
#include "geometry.h"

#include <stdio.h>

static int program_gc(lua_State *L)
{
	struct program *p = lua_touserdata(L, -1);
	if (p)
		program_destroy(p);
	return 0;
}

void program_init(struct program *p)
{
	p->program = glCreateProgram();
	p->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	p->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	p->vertex_text = "";
	p->fragment_text = "";
	p->linked = false;
	glAttachShader(p->program, p->vertex_shader);
	glAttachShader(p->program, p->fragment_shader);
}

void lprogram_create(lua_State *L)
{
	struct program *program = lua_newuserdata(L, sizeof(struct program));
	program_init(program);
	int program_idx = lua_gettop(L);
	lua_newtable(L);
	lua_pushcfunction(L, program_gc);
	lua_setfield(L, -2, "__gc");
	lua_setmetatable(L, program_idx);
}

bool lprogram_set_shaders(lua_State *L, const char *vs_text, const char *fs_text)
{
	struct program *program = lua_touserdata(L, -1);
	if ((vs_text && fs_text) && (strcmp(program->vertex_text, vs_text) || strcmp(program->fragment_text, fs_text))) {
		program->linked = false;
		program->vertex_text = strdup(vs_text);
		program->fragment_text = strdup(fs_text);
		if (!program_compile(program)) {
			return false;
		}
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
	return program->linked;
}

bool program_compile(struct program *p)
{
	glShaderSource(p->vertex_shader, 1, &p->vertex_text, NULL);
	glShaderSource(p->fragment_shader, 1, &p->fragment_text, NULL);
	glCompileShader(p->vertex_shader);
	glCompileShader(p->fragment_shader);

	char info_log[1000];
	GLint ret;

	glGetShaderiv(p->vertex_shader, GL_COMPILE_STATUS, &ret);
	if (ret == GL_FALSE) {
		glGetShaderInfoLog(p->vertex_shader, 1000, NULL, info_log);
		fprintf(stderr, "Vertex shader compile failed:\n %s", info_log);
		return false;
	}

	glGetShaderiv(p->fragment_shader, GL_COMPILE_STATUS, &ret);
	if (ret == GL_FALSE) {
		glGetShaderInfoLog(p->fragment_shader, 1000, NULL, info_log);
		fprintf(stderr, "Fragment shader compile failed:\n %s", info_log);
		return false;
	}
	return true;
}

bool program_link(struct program *p)
{
	GLint link_status;
	glLinkProgram(p->program);
	glGetProgramiv(p->program, GL_LINK_STATUS, &link_status);
	if (link_status == GL_FALSE) {
		char info_log[1000];
		glGetProgramInfoLog(p->program, 1000, NULL, info_log);
		fprintf(stderr, "Program link failed:\n %s\n", info_log);
	}
	p->linked = link_status == GL_TRUE;
	return link_status;
}

void program_destroy(struct program *p)
{
	glDeleteProgram(p->program);
	glDeleteShader(p->vertex_shader);
	glDeleteShader(p->fragment_shader);
}
