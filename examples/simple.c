#include <stdlib.h>

#include "glwin.h"
#include "gltext.h"
#include "glb-glcore.h"

gltext_renderer_t g_renderer;
struct gltext_font g_fonts[1];

void on_redraw(struct glwin *win)
{
	int width, height;
	width = win->width;
	height = win->height;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	float mvp[16] = {
		2.0/width,0,0,0,
		0,-2.0/height,0,0,
		0,0,1,0,
		-1,0,0,1};

	const char *str = "The quick brown fox jumps over the lazy dog()'\"0123456789`~!@#$%^&*()_+;/?.>,<={}[]\\";
	struct gltext_glyph_instance *r = gltext_renderer_prepare_render(g_renderer, strlen(str));

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
		struct gltext_glyph *g_cur = g_fonts[0].glyph_array + (*str);
		x_pos += gltext_get_advance(g_prev, g_cur);
		r->pos[0] = x_pos;
		r->pos[1] = y_pos;
		r->w = g_cur->w;
		r->color = color;
		r++;
		str++;
		g_prev = g_cur;
	}
	gltext_renderer_submit_render(g_renderer, mvp);
	glwin_swap_buffers(win);
}

void on_destroy(struct glwin *win)
{
	glwin_manager_destroy_window(win);
}

int main()
{
	struct glwin_callbacks cb = {
		.on_redraw = on_redraw,
		.on_destroy = on_destroy
	};

	g_renderer = gltext_renderer_new();

	glwin_manager_init();
	struct glwin *win = glwin_manager_create_window("Simple text test", &cb, 1024, 256);
	glwin_show_window(win);
	GLXContext ctx = glwin_create_context(win, 3, 3);
	glwin_manager_make_current(win, ctx);

	const char *charset = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'\"0123456789`~!@#$%^&*()_+;/?.>,<={}[]\\";
	struct gltext_font_desc font_desc = {
		.typeface = gltext_renderer_get_typeface(g_renderer, "ttf/LiberationSans-Regular.ttf"),
		.width = 20,
		.height = 20,
		.charset = charset
	};
	if (!gltext_renderer_initialize(g_renderer, &font_desc, 1, g_fonts)) {
		exit(-1);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	while (glwin_manager_process_events()) {
		glwin_manager_wait_events();
	}
}
