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

/*
 * glplatform_init()
 *
 * Performs one time initializtion of gplatform library. Must be called
 * before any other glplatform calls are made.
 *
 */
bool glplatform_init();

/*
 *
 * glplatform_shutdown()
 *
 * Free any resources allocated by glplatform. No glplatform calls
 * should be made after glplatform_shutdown()
 *
 */
void glplatform_shutdown();

/*
 * glplatform_create_window()
 *
 * Create an OpenGL enabled window.
 *
 * title - Title of the window
 *
 * callbacks - Functions to call when window events occur
 *
 * width - Desired width of window
 *
 * height - Desired height of window
 *
 */
struct glplatform_win *glplatform_create_window(const char *title,
		struct glplatform_win_callbacks *callbacks,
		int width,
		int height);

/*
 * glplatform_destroy_window
 *
 * Destroy a previously created window. The window structure will
 * be deallocated and no further callbacks will be issued for
 * it.
 *
 */
void glplatform_destroy_window(struct glplatform_win *win);


/*
 * glplatform_get_thread_state()
 *
 * Store OpenGL related thread state. Should be called
 * before calling glplatform_make_current() if the current
 * thread state is not known and will need to be restored.
 *
 */
void glplatform_get_thread_state(struct glplatform_thread_state *state);

/*
 * glplatform_get_thread_state()
 *
 * Restore OpenGL thread state retrieved by
 * glplatform_get_thread_state()
 *
 */
void glplatform_set_thread_state(const struct glplatform_thread_state *state);

/*
 * glplatform_get_events()
 *
 * Collect events into glplatform's internal queue. If 'block' is set to true
 * then wait until an event occurs.
 *
 * Returns the number of events queued or -1 on error
 *
 */
int glplatform_get_events(bool block);

/*
 * glplatform_make_current()
 *
 * Make 'context' current for this thread. All subsequent OpenGL calls
 * in the current thread will execute in this context.
 *
 */
void glplatform_make_current(struct glplatform_win *win, glplatform_gl_context_t context);

/*
 * glplatform_process_events()
 *
 * Issue callbacks for events queued by glplatform_get_events()
 *
 * Returns true if at least one window is still exists
 *
 */
bool glplatform_process_events();

/*
 * glplatform_fd_bind()
 *
 * Causes glplatform to call win->on_fd_event() whenever the
 * supplied file descriptor's read, write, or error status
 * changes.
 *
 */
void glplatform_fd_bind(int fd, struct glplatform_win *win);


/*
 * glplatform_fd_unbind()
 *
 * Causes glplatform to stop calling win->on_fd_event()
 * for the supplied file descriptor.
 *
 */
void glplatform_fd_unbind(int fd);

/*
 * glplatform_create_context()
 *
 * Attempts to create a core-profile OpenGL context that is backwards
 * compatible with the supplied version number.
 *
 */
glplatform_gl_context_t glplatform_create_context(struct glplatform_win *win, int maj_ver, int min_ver);

enum glplatform_win_types {
	GLWIN_POPUP,
	GLWIN_NORMAL,
	GLWIN_DIALOG,
	GLWIN_TOOLBAR,
	GLWIN_UTILITY
};

/*
 * glplatform_set_win_type()
 *
 * Set a window's type which determines it's border and stacking behavior.
 *
 */
void glplatform_set_win_type(struct glplatform_win *win, enum glplatform_win_types type);

/*
 * glplatform_set_win_transient_for()
 *
 * Make this window a 'transient' for the window with the specified xid.
 * A glplatform window's xid is stored in the 'window' field of it's
 * glplatform_win structure.
 *
 */
void glplatform_set_win_transient_for(struct glplatform_win *win, intptr_t xid);

/*
 * glplatform_swap_buffers()
 *
 * Swap a windows backbuffer to the front.
 *
 */
void glplatform_swap_buffers(struct glplatform_win *win);

/*
 * glplatform_show_window()
 *
 * Make a window visible. Windows are hidden at creation time.
 *
 */
void glplatform_show_window(struct glplatform_win *win);

/*
 * glplatform_fullscreen_win()
 *
 * Change a window's fullscreen status. Windows are initially
 * not fullscreen.
 *
 */
void glplatform_fullscreen_win(struct glplatform_win *win, bool fullscreen);

/*
 * glplatform_is_button_pressed()
 *
 * Returns true if specified mouse button number is pressed. The left
 * button is numbered 0. The middle button is numbered 1. The right
 * button is numbered 2.
 *
 */
bool glplatform_is_button_pressed(struct glplatform_win *win, int button_no);

/*
 * glplatform_is_shift_pressed()
 *
 * Returns true if the shift key is being held
 *
 */
bool glplatform_is_shift_pressed(struct glplatform_win *win);

/*
 * glplatform_is_control_pressed()
 *
 * Returns true if the control key is being held
 *
 */
bool glplatform_is_control_pressed(struct glplatform_win *win);

#endif
