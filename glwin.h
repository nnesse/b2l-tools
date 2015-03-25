#ifndef GL_WIN_H
#define GL_WIN_H

#include <stdint.h>
#include <X11/Xlib.h>

#define GLB_ENABLE_GLX_ARB_create_context
#define GLB_ENABLE_GLX_ARB_create_context_profile
#include "glb-glx.h"

struct glwin;

struct glwin_callbacks {
	void (*on_create)(struct glwin *win);
	void (*on_resize)(struct glwin *win);
	void (*on_redraw)(struct glwin *win);
	void (*on_mouse_button_up)(struct glwin *, int, int, int);
	void (*on_mouse_button_down)(struct glwin *, int, int, int);
	void (*on_mouse_move)(struct glwin *, int, int);
	void (*on_mouse_wheel)(struct glwin *, int, int, int);
	void (*on_key_down)(struct glwin *, int);
	void (*on_key_up)(struct glwin *, int);
	void (*on_destroy)(struct glwin *);
	void (*on_fd_event)(struct glwin *, int, uint32_t);
	void (*on_x_event)();
};

struct glwin {
	Window window;
	GLXFBConfig fb_config;
	GLXWindow glx_window;
	struct glwin_callbacks callbacks;
	int width;
	int height;
	XEvent current_event;
	int x_state_mask;
	struct glwin *next;
	struct glwin **pprev;
};

bool glwin_manager_init();
void glwin_manager_shutdown();

struct glwin *glwin_manager_create_window(const char *title,
		struct glwin_callbacks *callbacks,
		int width,
		int height);

void glwin_manager_make_current(struct glwin *win, GLXContext context);
bool glwin_manager_process_events();
int glwin_manager_wait_events();
void glwin_manager_destroy_window(struct glwin *win);
void glwin_manager_fd_bind(int fd, struct glwin *win);
void glwin_manager_fd_unbind(int fd);

GLXContext glwin_create_context(struct glwin *win, int maj_ver, int min_ver);
void glwin_swap_buffers(struct glwin *win);
void glwin_show_window(struct glwin *win);

bool glwin_is_button_pressed(struct glwin *win, int button_no);

bool glwin_is_modifier_pressed(struct glwin *win, int modifier_no);

extern int glwin_epoll_fd;

#endif
