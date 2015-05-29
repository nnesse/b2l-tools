#include "glwin.h"
#include "glb-glcore.h"

#include <stdlib.h>

bool fullscreen = false;

void on_expose(struct glwin *win)
{
	glClearColor(0,0,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glwin_swap_buffers(win);
}

void on_key_down(struct glwin *win, int k)
{
	if (k == 'f') {
		fullscreen = !fullscreen;
		glwin_fullscreen(win, fullscreen);
	}
}

void on_destroy(struct glwin *win)
{
	glwin_destroy_window(win);
}

int main()
{
	struct glwin_callbacks cb = {
		.on_expose = on_expose,
		.on_destroy = on_destroy,
		.on_key_down = on_key_down
	};
	glwin_init();
	struct glwin *win = glwin_create_window("Hello window", &cb, 512, 512);
	if (!win)
		exit(-1);

	glwin_show_window(win);
	glwin_context_t ctx = glwin_create_context(win, 3, 3);
	if (!ctx)
		exit(-1);
	glwin_make_current(win, ctx);
	glb_glcore_init(3, 3);
	while (glwin_process_events()) {
		if (glwin_get_events(true) < 0)
			break;
	}
}
