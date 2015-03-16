#include "glwin.h"
#include "glb-glcore.h"

#include <stdlib.h>

void on_redraw(struct glwin *win)
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
		.on_redraw = on_redraw,
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
	while (glwin_manager_process_events()) {
		glwin_manager_wait_events();
	}
}
