#include <stdlib.h>
#include <stdio.h>

#include "glplatform.h"
#include "gltext.h"
#include "glb-glcore.h"

void on_destroy(struct glplatform_win *win)
{
	glplatform_destroy_window(win);
}

int main()
{
	gltext_renderer_t renderer;
	gltext_font_t font;

	struct glplatform_win_callbacks cb = {
		.on_destroy = on_destroy
	};

	renderer = gltext_renderer_new(" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'\"0123456789`~!@#$%^&*()_+;/?.>,<={}[]\\");

	if (!glplatform_init()) {
		fprintf(stderr, "Failed to initialize GL window manager\n");
		exit(-1);
	}

	struct glplatform_win *win = glplatform_create_window("Simple text test", &cb, 1024, 256);
	if (!win) {
		fprintf(stderr, "Failed to create OpenGL window\n");
		exit(-1);
	}
	glplatform_show_window(win);
	glplatform_gl_context_t ctx = glplatform_create_context(win, 3, 3);
	if (!ctx) {
		fprintf(stderr, "Failed to create OpenGL context\n");
		return 0;
	}
	glplatform_make_current(win, ctx);
	glb_glcore_init(3, 3);

	font = gltext_font_create(renderer, gltext_renderer_get_typeface(renderer, TTF_PATH "/LiberationSans-Regular.ttf"), 20);
	if (!font) {
		fprintf(stderr, "Failed to create font\n");
		exit(-1);
	}

	while (glplatform_process_events()) {
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
		struct gltext_glyph_instance *r = gltext_renderer_prepare_render(renderer, font, strlen(str));

		const struct gltext_glyph *g_prev = NULL;
		float x_pos = 0;
		float y_pos = 0;
		struct gltext_color color = {
			.r = 1,
			.g = 1,
			.b = 1,
			.a = 1
		};
		while (*str) {
			const struct gltext_glyph *g_cur = gltext_get_glyph(font, *str);
			x_pos += gltext_get_advance(g_prev, g_cur);
			r->pos[0] = x_pos;
			r->pos[1] = y_pos;
			r->w = g_cur->w;
			r++;
			str++;
			g_prev = g_cur;
		}
		gltext_renderer_submit_render(renderer, &color, mvp);
		glplatform_swap_buffers(win);

		if (glplatform_get_events(true) < 0)
			break;
	}
	return 0;
}
