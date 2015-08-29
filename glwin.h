#ifndef GL_WIN_H
#define GL_WIN_H

#include <stdint.h>
#include <stdbool.h>

struct glwin;

typedef void * glwin_context_t;

struct glwin_callbacks {
	void (*on_create)(struct glwin *win);
	void (*on_resize)(struct glwin *win);
	void (*on_expose)(struct glwin *win);
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
	uint32_t window; //Window
	void *fb_config; //GLXFBConfig
	uint32_t glx_window; //GLXWindow
	struct glwin_callbacks callbacks;
	int width;
	int height;
	int x_state_mask;
	struct glwin *next;
	struct glwin **pprev;
};

struct glwin_thread_state {
	void *display;
	void *context;
	uint32_t read_draw;
	uint32_t write_draw;
};

bool glplatform_init();
void glplatform_shutdown();

struct glwin *glplatform_create_window(const char *title,
		struct glwin_callbacks *callbacks,
		int width,
		int height);

void glplatform_destroy_window(struct glwin *win);

void glplatform_get_thread_state(struct glwin_thread_state *state);

void glplatform_set_thread_state(const struct glwin_thread_state *state);

int glplatform_get_events(bool block);

void glplatform_make_current(struct glwin *win, glwin_context_t context);

bool glplatform_process_events();

void glplatform_fd_bind(int fd, struct glwin *win);

void glplatform_fd_unbind(int fd);

glwin_context_t glplatform_create_context(struct glwin *win, int maj_ver, int min_ver);

extern int glplatform_epoll_fd;

enum glwin_types {
	GLWIN_POPUP,
	GLWIN_NORMAL,
	GLWIN_DIALOG,
	GLWIN_TOOLBAR,
	GLWIN_UTILITY
};

void glwin_set_type(struct glwin *win, enum glwin_types type);

void glwin_set_transient_for(struct glwin *win, intptr_t id);
void glwin_swap_buffers(struct glwin *win);
void glwin_show_window(struct glwin *win);
void glwin_fullscreen(struct glwin *win, bool fullscreen);

bool glwin_is_button_pressed(struct glwin *win, int button_no);

bool glwin_is_modifier_pressed(struct glwin *win, int modifier_no);

#endif
