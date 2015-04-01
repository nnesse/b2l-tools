#include "glwin.h"
#include "glb-glcore.h"

#include <stdlib.h>

void on_expose(struct glwin *win)
{
	glClearColor(0,0,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glwin_swap_buffers(win);
}

void on_destroy(struct glwin *win)
{
	glwin_manager_destroy_window(win);
}

int main()
{
	struct glwin_callbacks cb = {
		.on_expose = on_expose,
		.on_destroy = on_destroy
	};
	glwin_manager_init();
	struct glwin *win = glwin_manager_create_window("Hello window", &cb, 512, 512);
	if (!win)
		exit(-1);

	glwin_show_window(win);
	GLXContext ctx = glwin_create_context(win, 3, 3);
	if (!ctx)
		exit(-1);
	glwin_manager_make_current(win, ctx);
	glb_glcore_init(3, 3);
	while (glwin_manager_process_events()) {
		if (glwin_manager_get_events(true) < 0)
			break;
	}
}
