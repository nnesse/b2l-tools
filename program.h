#ifndef PROGRAM_H
#define PROGRAM_H

#include "glplatform-glcore.h"

#include "lua.h"

struct program {
	const char *vertex_text;
	const char *fragment_text;
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint program;
	bool linked;
};

void program_init(struct program *p);

bool program_compile(struct program *p);

bool program_link(struct program *p);

void program_destroy(struct program *p);

void lprogram_create(lua_State *L);

bool lprogram_set_shaders(lua_State *L, const char *vs_text, const char *fs_text);

#endif
