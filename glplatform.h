#ifndef GL_WIN_H
#define GL_WIN_H

#include <stdint.h>
#include <stdbool.h>

struct glplatform_win;

typedef void * glplatform_gl_context_t;

/*
 * epoll file descriptor used for event waiting. Can be used to integrate 
 * glplatform into a different event loop.
 *
 */
extern int glplatform_epoll_fd;

struct glplatform_win_callbacks {
	void (*on_create)(struct glplatform_win *win);
	void (*on_resize)(struct glplatform_win *win);
	void (*on_expose)(struct glplatform_win *win);
	void (*on_mouse_button_up)(struct glplatform_win *, int, int, int);
	void (*on_mouse_button_down)(struct glplatform_win *, int, int, int);
	void (*on_mouse_move)(struct glplatform_win *, int, int);
	void (*on_mouse_wheel)(struct glplatform_win *, int, int, int);
	void (*on_key_down)(struct glplatform_win *, int);
	void (*on_key_up)(struct glplatform_win *, int);
	void (*on_destroy)(struct glplatform_win *);
	void (*on_fd_event)(struct glplatform_win *, int, uint32_t);
	void (*on_x_event)();
};

struct glplatform_win {
	uint32_t window; //Window
	void *fb_config; //GLXFBConfig
	uint32_t glx_window; //GLXWindow
	struct glplatform_win_callbacks callbacks;
	int width;
	int height;
	int x_state_mask;
	struct glplatform_win *next;
	struct glplatform_win **pprev;
};

struct glplatform_thread_state {
	void *display;
	void *context;
	uint32_t read_draw;
	uint32_t write_draw;
};

bool glplatform_init();
void glplatform_shutdown();

struct glplatform_win *glplatform_create_window(const char *title,
		struct glplatform_win_callbacks *callbacks,
		int width,
		int height);

void glplatform_destroy_window(struct glplatform_win *win);

void glplatform_get_thread_state(struct glplatform_thread_state *state);

void glplatform_set_thread_state(const struct glplatform_thread_state *state);

int glplatform_get_events(bool block);

void glplatform_make_current(struct glplatform_win *win, glplatform_gl_context_t context);

bool glplatform_process_events();

void glplatform_fd_bind(int fd, struct glplatform_win *win);

void glplatform_fd_unbind(int fd);

glplatform_gl_context_t glplatform_create_context(struct glplatform_win *win, int maj_ver, int min_ver);

extern int glplatform_epoll_fd;

enum glplatform_win_types {
	GLWIN_POPUP,
	GLWIN_NORMAL,
	GLWIN_DIALOG,
	GLWIN_TOOLBAR,
	GLWIN_UTILITY
};

void glplatform_set_win_type(struct glplatform_win *win, enum glplatform_win_types type);

void glplatform_set_win_transient_for(struct glplatform_win *win, intptr_t id);
void glplatform_swap_buffers(struct glplatform_win *win);
void glplatform_show_window(struct glplatform_win *win);
void glplatform_fullscreen_win(struct glplatform_win *win, bool fullscreen);

bool glplatform_is_button_pressed(struct glplatform_win *win, int button_no);

bool glplatform_is_modifier_pressed(struct glplatform_win *win, int modifier_no);

#endif
