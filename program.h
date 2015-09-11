#ifndef PROGRAM_H
#define PROGRAM_H

#include "glplatform-glcore.h"

struct program {
	const char *vertex_text;
	const char *fragment_text;
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint program;
};

void program_init(struct program *p);

bool program_compile(struct program *p);

bool program_link(struct program *p);

void program_destroy(struct program *p);

#endif
