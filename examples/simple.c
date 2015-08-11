#include <stdlib.h>
#include <stdio.h>

#include "glwin.h"
#include "gltext.h"
#include "glb-glcore.h"

gltext_renderer_t g_renderer;
gltext_font_t g_font;

void on_expose(struct glwin *win)
{
	int width, height;
	width = win->width;
	height = win->height;
	glViewport(0, 0, width, height);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	float mvp[16] = {
		2.0/width,0,0,0,
		0,-2.0/height,0,0,
		0,0,1,0,
		-1,0,0,1};

	const char *str = "The quick brown fox jumps over the lazy dog()'\"0123456789`~!@#$%^&*()_+;/?.>,<={}[]\\";
	struct gltext_glyph_instance *r = gltext_renderer_prepare_render(g_renderer, g_font, strlen(str));

	struct gltext_glyph *g_prev = NULL;
	float x_pos = 0;
	float y_pos = 0;
	struct gltext_color color = {
		.r = 1,
		.g = 1,
		.b = 1,
		.a = 1
	};
	while (*str) {
		struct gltext_glyph *g_cur = gltext_get_glyph(g_font, *str);
		x_pos += gltext_get_advance(g_prev, g_cur);
		r->pos[0] = x_pos;
		r->pos[1] = y_pos;
		r->w = g_cur->w;
		r++;
		str++;
		g_prev = g_cur;
	}
	gltext_renderer_submit_render(g_renderer, &color, mvp);
	glwin_swap_buffers(win);
}

void on_destroy(struct glwin *win)
{
	glwin_destroy_window(win);
}

int main()
{
	struct glwin_callbacks cb = {
		.on_expose = on_expose,
		.on_destroy = on_destroy
	};

	g_renderer = gltext_renderer_new(" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'\"0123456789`~!@#$%^&*()_+;/?.>,<={}[]\\");

	if (!glwin_init()) {
		fprintf(stderr, "Failed to initialize GL window manager\n");
		exit(-1);
	}

	struct glwin *win = glwin_create_window("Simple text test", &cb, 1024, 256);
	if (!win) {
		fprintf(stderr, "Failed to create OpenGL window\n");
		exit(-1);
	}
	glwin_show_window(win);
	glwin_context_t ctx = glwin_create_context(win, 3, 3);
	if (!ctx) {
		fprintf(stderr, "Failed to create OpenGL context\n");
		return 0;
	}
	glwin_make_current(win, ctx);
	glb_glcore_init(3, 3);

	g_font = gltext_font_create(g_renderer, gltext_renderer_get_typeface(g_renderer, TTF_PATH "/LiberationSans-Regular.ttf"), 20);
	if (!g_font) {
		fprintf(stderr, "Failed to create font\n");
		exit(-1);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	while (glwin_process_events()) {
		if (glwin_get_events(true) < 0)
			break;
	}
}
