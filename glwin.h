#ifndef GL_WIN_H
#define GL_WIN_H

#include <stdint.h>
#include <X11/Xlib.h>
#include "glx_1_4.h"

#include "list.h"

struct glwin;

struct glwin_callbacks {
	void (*on_create)(struct glwin *win);
	void (*on_resize)(struct glwin *win);
	void (*on_redraw)(struct glwin *win);
	void (*on_lbutton_down)(struct glwin *, int, int);
	void (*on_lbutton_up)(struct glwin *, int, int);
	void (*on_rbutton_down)(struct glwin *, int, int);
	void (*on_rbutton_up)(struct glwin *, int, int);
	void (*on_mouse_move)(struct glwin *, int, int, int, int);
	void (*on_mouse_wheel)(struct glwin *, int, int, int);
	void (*on_key_down)(struct glwin *, int);
	void (*on_key_up)(struct glwin *, int);
	void (*on_destroy)(struct glwin *);
	void (*on_fd_event)(struct glwin *, int, uint32_t);
};

struct glwin {
	Window window;
	GLXFBConfig fb_config;
	GLXWindow glx_window;
	struct glwin_callbacks callbacks;
	int win_width;
	int win_height;
	int socket_fd;
	struct hlist_node node;	
};

bool glwin_manager_init();
void glwin_manager_shutdown();

struct glwin *glwin_manager_create_window(const char *title,
		struct glwin_callbacks *callbacks,
		int width,
		int height);

void glwin_manager_make_current(struct glwin *win, GLXContext context);
bool glwin_manager_process_events();
void glwin_manager_wait_events();
void glwin_manager_destroy_window(struct glwin *win);
void glwin_manager_fd_bind(int fd, struct glwin *win);
void glwin_manager_fd_unbind(int fd);

GLXContext glwin_create_context(struct glwin *win, int maj_ver, int min_ver);
void glwin_swap_buffers(struct glwin *win);
void glwin_show_window(struct glwin *win);

#endif
