#include "glplatform.h"
#include "glplatform-glcore.h"

#include <stdlib.h>

bool fullscreen = false;

void on_expose(struct glplatform_win *win)
{
	glClearColor(0,0,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glplatform_swap_buffers(win);
}

void on_key_down(struct glplatform_win *win, int k)
{
	if (k == 'f') {
		fullscreen = !fullscreen;
		glplatform_fullscreen_win(win, fullscreen);
	}
}

void on_destroy(struct glplatform_win *win)
{
	glplatform_destroy_window(win);
}

int main()
{
	struct glplatform_win_callbacks cb = {
		.on_expose = on_expose,
		.on_destroy = on_destroy,
		.on_key_down = on_key_down
	};
	if (!glplatform_init()) {
		exit(-1);
	}
	struct glplatform_win *win = glplatform_create_window("Hello window", &cb, NULL, 512, 512);
	if (!win)
		exit(-1);

	glplatform_show_window(win);
	glplatform_gl_context_t ctx = glplatform_create_context(win, 3, 3);
	if (!ctx)
		exit(-1);
	glplatform_make_current(win, ctx);
	if (!glplatform_glcore_init(3, 3)) {
		exit(-1);
	}
	while (glplatform_process_events()) {
		if (glplatform_get_events(true) < 0)
			break;
	}
}
