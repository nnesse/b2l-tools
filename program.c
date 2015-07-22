#include "program.h"

#include <stdio.h>

void program_init(struct program *p)
{
	p->program = glCreateProgram();
	p->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	p->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glAttachShader(p->program, p->vertex_shader);
	glAttachShader(p->program, p->fragment_shader);
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
	return link_status;
}

void program_destroy(struct program *p)
{
	glDeleteProgram(p->program);
	glDeleteShader(p->vertex_shader);
	glDeleteShader(p->fragment_shader);
}
