#ifndef GL_WIN_H
#define GL_WIN_H

#include <stdint.h>
#include <stdbool.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <X11/Xlib.h>
#endif

struct glplatform_win;

typedef intptr_t glplatform_gl_context_t;

/*
 * int glplatform_epoll_fd;
 *
 * epoll file descriptor used by glplatform for event waiting. Can be used to
 * integrate glplatform into a different event loop.
 *
 */
extern int glplatform_epoll_fd;

/*
 * struct glplatform_win_callbacks
 *
 * Callbacks for windows created by glplatform
 *
 */
struct glplatform_win_callbacks {
	/*
	 * on_create(win)
	 *
	 * Called when the window is created.
	 *
	 * win - Window
	 *
	 */
	void (*on_create)(struct glplatform_win *win);

	/*
	 * on_resize(win)
	 *
	 * Called when window is resized. The new window
	 * size can be read from the window structure.
	 *
	 * win - Window
	 *
	 */
	void (*on_resize)(struct glplatform_win *win);

	/*
	 * on_expose(win)
	 *
	 * Called when a part of the window was hidden and is
	 * now exposed.
	 *
	 * win - Window
	 *
	 */
	void (*on_expose)(struct glplatform_win *win);

	/*
	 *
	 * on_mouse_button_up(win, button_num, mouse_x, mouse_y)
	 *
	 * Called when a mouse button is released
	 *
	 * win - Window
	 *
	 * button_num - Button released
	 *
	 * mouse_x,mouse_y - Mouse position
	 *
	 */
	void (*on_mouse_button_up)(struct glplatform_win *, int button_num, int mouse_x, int mouse_y);

	/*
	 *
	 * on_mouse_button_down(win, button_num, mouse_x, mouse_y)
	 *
	 * Called when a mouse button is pressed
	 *
	 * win - Window
	 *
	 * button_num - Button pressed
	 *
	 * mouse_x,mouse_y - Mouse position
	 *
	 */
	void (*on_mouse_button_down)(struct glplatform_win *, int button_num, int mouse_x, int mouse_y);

	/*
	 *
	 * on_mouse_button_move(win, button_num, mouse_x, mouse_y)
	 *
	 * Called when the mouse moves in the window area
	 *
	 * win - Window
	 *
	 * mouse_x,mouse_y - Mouse position
	 *
	 */
	void (*on_mouse_move)(struct glplatform_win *, int mouse_x, int mouse_y);

	/*
	 *
	 * on_mouse_wheel(win, button_num, mouse_x, mouse_y, delta)
	 *
	 * Called when the mouse wheel changes position
	 *
	 * win - window
	 *
	 * mouse_x,mouse_y - Mouse position
	 *
	 * delta - Direction the mouse wheel moved.
	 *
	 * 	+1: Mouse wheel moved up
	 *
	 * 	-1: Mouse wheel moved down
	 */
	void (*on_mouse_wheel)(struct glplatform_win *, int mouse_x, int mouse_y, int delta);

	/*
	 * on_key_down(win, key)
	 *
	 * Called when a key is pressed
	 *
	 * win - Window
	 *
	 * key - ASCII value of key pressed
	 *
	 */
	void (*on_key_down)(struct glplatform_win *, int key);

	/*
	 * on_key_down(win, key)
	 *
	 * Called when a key is released
	 *
	 * win - Window
	 *
	 * key - ASCII code of key released
	 *
	 */
	void (*on_key_up)(struct glplatform_win *, int key);

	/*
	 * on_destroy(win)
	 *
	 * Called when the window's close button has been pressed
	 *
	 * win - Window
	 *
	 */
	void (*on_destroy)(struct glplatform_win *);

	/*
	 * on_fd_event(win, fd, event)
	 *
	 * Called when the window's close button has been pressed
	 *
	 * win - Window
	 *
	 * fd - File descriptor that changed status
	 *
	 * event - Event mask returned from epoll(). See 'man epoll_ctl' for full descriptions.
	 *
	 * 	EPOLLIN: File descriptor has become readable
	 *
	 * 	EPOLLOUT: File descriptor has become writable
	 *
	 * 	EPOLLERR: File descriptor encountered an error
	 *
	 * 	EPOLLRDHUP: Peer closed connection
	 *
	 * user_data - User data value passed to glplatform_fd_bind()
	 *
	 */
	void (*on_fd_event)(struct glplatform_win *, int fd, uint32_t event, intptr_t user_data);

#ifndef _WIN32
	/*
	 * on_x_event(event)
	 *
	 * Called for all X event's processed. Can be used to process events
	 * not processed by glplatform.
	 *
	 * win - Window
	 *
	 * event - X event
	 *
	 */
	void (*on_x_event)(struct glplatform_win *, XEvent *event);
#endif
};

struct glplatform_fbformat {
	int color_bits;
	int alpha_bits;
	int stencil_bits;
	int depth_bits;
	int accum_bits;
};

struct glplatform_win {
#ifdef _WIN32
	int pixel_format;
	HDC hdc;
	HWND hwnd;
#else
	uint32_t window; //Window xid
	void *fb_config; //GLXFBConfig
	uint32_t glx_window; //GLXWindow
	int x_state_mask;
	uint32_t colormap; //Colormap
#endif
	struct glplatform_fbformat fbformat;
	struct glplatform_win_callbacks callbacks;
	int width;
	int height;
	struct glplatform_win *next;
	struct glplatform_win **pprev;
};

#ifndef _WIN32
struct glplatform_thread_state {
	void *display;
	void *context;
	uint32_t read_draw;
	uint32_t write_draw;
};
#endif

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
 * fbformat - Format of framebuffer requested. If NULL a 24-bit
 * 	color buffer and 24-bit depth buffer will be requests with
 *	no stencil, accumulation, or alpha bits.
 *
 * width - Desired width of window
 *
 * height - Desired height of window
 *
 */
struct glplatform_win *glplatform_create_window(const char *title,
		const struct glplatform_win_callbacks *callbacks,
		const struct glplatform_fbformat *fbformat,
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
 * Returns non-zero if events have been queued. Returns zero if no events are queued
 * and negative on error.
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
 * fd - File descriptor to bind
 *
 * win - Window to bind to the file descriptor
 *
 * user_data - Data to pass to the on_fd_event() callback
 *
 */
void glplatform_fd_bind(int fd, struct glplatform_win *win, intptr_t user_data);


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
