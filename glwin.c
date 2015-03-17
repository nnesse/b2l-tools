#define GLB_ENABLE_GLX_create_context
#define GLB_ENABLE_GLX_create_context_profile
#include "glwin.h"

#include <X11/Xlib.h>
#include <sys/epoll.h>
#include <sys/resource.h>
#include <stdlib.h>

static int g_epoll_fd;
static int g_x11_fd;
static int g_event_count;
static struct epoll_event g_events[100];
static Display *g_display;
static int g_screen;
static Atom g_delete_atom;

struct glwin *g_win_list = NULL;
int g_glwin_count = 0;
struct glwin **g_fd_binding;

static struct glwin *find_glwin(Window w)
{
	struct glwin *win = g_win_list;
	while (win) {
		if (win->window == w)
			return win;
		win = win->next;
	}
	return NULL;
}

static void retire_glwin(struct glwin *win)
{
	struct glwin *pos = g_win_list;
	while (win) {
		if (pos == win) {
			*(pos->pprev) = pos->next;
			pos->next->pprev = pos->pprev;
			g_glwin_count--;
			break;
		}
		pos = pos->next;
	}
}

static void register_glwin(struct glwin *win)
{
	struct glwin *test = find_glwin(win->window);
	if (test)
		return;
	g_glwin_count++;
	win->next = g_win_list;
	win->pprev = &g_win_list;
	g_win_list = win;
}

static void on_mouse_wheel(struct glwin *win, int x, int y, int a)
{
	if (win->callbacks.on_mouse_wheel)
		win->callbacks.on_mouse_wheel(win, x, y, a);
}

bool glwin_is_button_pressed(struct glwin *win, int button)
{
	switch (button)
	{
	case 1:
		return win->x_state_mask & Button1Mask;
		break;
	case 2:
		return win->x_state_mask & Button2Mask;
		break;
	case 3:
		return win->x_state_mask & Button3Mask;
		break;
	}
	return false;
}

bool glwin_is_modifier_pressed(struct glwin *win, int mod)
{
	switch (mod)
	{
	case 1:
		return win->x_state_mask & Mod1Mask;
		break;
	case 2:
		return win->x_state_mask & Mod2Mask;
		break;
	case 3:
		return win->x_state_mask & Mod3Mask;
		break;
	case 4:
		return win->x_state_mask & Mod4Mask;
		break;
	case 5:
		return win->x_state_mask & Mod5Mask;
		break;
	}
	return false;
}

bool glwin_is_shift_pressed(struct glwin *win)
{
	return win->x_state_mask & Mod1Mask;
}

static int handle_x_event(struct glwin *win, XEvent *event)
{
	switch (event->type) {
	case ConfigureNotify: {
		XConfigureEvent *configure_event = (XConfigureEvent *)event;
		if (win->width != configure_event->width || win->height != configure_event->height) {
			win->width = configure_event->width;
			win->height = configure_event->height;
			if (win->callbacks.on_resize)
				win->callbacks.on_resize(win);
		}
	} break;
	case KeyPress: {
		char buf[20];
		XKeyEvent *key_event = (XKeyEvent *)event;
		KeySym k;
		win->x_state_mask = key_event->state;
		XLookupString(key_event, buf, 20, &k, NULL);
		if (win->callbacks.on_key_down)
			win->callbacks.on_key_down(win, k);
	} break;
	case KeyRelease: {
		char buf[20];
		XKeyEvent *key_event = (XKeyEvent *)event;
		KeySym k;
		win->x_state_mask = key_event->state;
		XLookupString(key_event, buf, 20, &k, NULL);
		if (win->callbacks.on_key_up)
			win->callbacks.on_key_up(win, k);
	} break;
	case ButtonPress: {
		XButtonEvent *button_event = (XButtonEvent *)event;
		win->x_state_mask = button_event->state;
		switch (button_event->button) {
		case 1:
		case 2:
		case 3:
			if (win->callbacks.on_mouse_button_down)
				win->callbacks.on_mouse_button_down(win, button_event->button, button_event->x, button_event->y);
			break;
		case 4:
			on_mouse_wheel(win, button_event->x, button_event->y, -1);
			break;
		case 5:
			on_mouse_wheel(win, button_event->x, button_event->y, 1);
			break;
		}
	} break;
	case ButtonRelease: {
		XButtonEvent *button_event = (XButtonEvent *)event;
		win->x_state_mask = button_event->state;
		switch (button_event->button) {
		case 1:
		case 2:
		case 3:
			if (win->callbacks.on_mouse_button_up)
				win->callbacks.on_mouse_button_up(win, button_event->button, button_event->x, button_event->y);
			break;
		}
	} break;
	case MotionNotify: {
		XMotionEvent *motion_event = (XMotionEvent *)event;
		win->x_state_mask = motion_event->state;
		if (win->callbacks.on_mouse_move)
			win->callbacks.on_mouse_move(win,
				motion_event->x,
				motion_event->y);
	} break;
	case Expose: {
		XExposeEvent *expose_event = (XExposeEvent *)event;
		if (expose_event->count == 0) {
			if(win->callbacks.on_redraw)
				win->callbacks.on_redraw(win);
		}
	} break;
	case ClientMessage: {
		XClientMessageEvent *client_event = (XClientMessageEvent *)event;
		if (client_event->data.l[0] == g_delete_atom)
			if (win->callbacks.on_destroy)
				win->callbacks.on_destroy(win);
	} break;
	default:
		break;
	}
	if (win->callbacks.on_x_event)
		win->callbacks.on_x_event(win);
	return 0;
}

bool glwin_manager_init()
{
	g_event_count = 0;
	g_epoll_fd = epoll_create1(0);
	g_display = XOpenDisplay(NULL);
	g_x11_fd = XConnectionNumber(g_display);
	glb_glx_init(1, 4);

	struct rlimit rl;
	int rc = getrlimit(RLIMIT_NOFILE, &rl);
	if (rc)
		return false;

	g_fd_binding = (struct glwin **)calloc(rl.rlim_max, sizeof(struct glwin *));
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = g_x11_fd;
	epoll_ctl(g_epoll_fd, EPOLL_CTL_ADD, g_x11_fd, &ev); //TODO: check for errors

	g_screen = DefaultScreen(g_display);
	g_delete_atom = XInternAtom(g_display, "WM_DELETE_WINDOW", True);
}

void glwin_manager_shutdown()
{
	XCloseDisplay(g_display);
}

struct glwin *glwin_manager_create_window(const char *title, struct glwin_callbacks *callbacks, int width, int height)
{
	GLXFBConfig fb_config;
	Window window;
	GLXWindow glx_window;

	int fb_attributes[] = {
		/* attribute/value pairs */
		GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
		GLX_RENDER_TYPE, GLX_RGBA_BIT,
		GLX_DOUBLEBUFFER, 1,
		GLX_RED_SIZE, 8,
		GLX_GREEN_SIZE, 8,
		GLX_BLUE_SIZE, 8,
		GLX_ALPHA_SIZE, 8,
		GLX_STENCIL_SIZE, 8,
		GLX_DEPTH_SIZE, 24,
		GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,

		/* terminator */
		None
	};

	XVisualInfo *visual_info;
	int fb_count;
	GLXFBConfig *fb_config_a;

	fb_config_a = glXChooseFBConfig(g_display, g_screen, fb_attributes, &fb_count);

	if (fb_count == 0) {
		return NULL;
	}

	fb_config = fb_config_a[0];

	visual_info = glXGetVisualFromFBConfig(g_display, fb_config);

	XSetWindowAttributes w_attr;
	w_attr.background_pixel = 0;
	w_attr.border_pixel = 0;
	w_attr.colormap = XCreateColormap(g_display, RootWindow(g_display, g_screen), visual_info->visual, AllocNone);

	window = XCreateWindow(g_display,
			       RootWindow(g_display, g_screen), /* parent */
			       0, 0,	/* x,y */
			       width, height, 0,	/* border width */
			       visual_info->depth,	/* depth */
			       InputOutput,	/* class */
			       visual_info->visual, CWColormap,	/* attribute valuemask */
			       &w_attr);	/*attributes */

	if (!window) {
		return NULL;
	}

	glx_window = glXCreateWindow(g_display, fb_config, window, NULL);

	XStoreName(g_display, window, title);

	//Tell X that we want to process delete window client messages
	Atom wm_atoms[] = { g_delete_atom };
	XSetWMProtocols(g_display, window, wm_atoms, 1);

	//Choose what X events we want to recieve
	XSelectInput(g_display,
		     window,
		     KeyPressMask |
		     ExposureMask |
		     KeyReleaseMask |
		     ButtonPressMask |
		     ButtonReleaseMask |
		     PointerMotionMask |
		     StructureNotifyMask |
		     SubstructureNotifyMask);

	struct glwin *win = (struct glwin *) malloc(sizeof(struct glwin));
	win->width = width;
	win->height = height;
	win->fb_config = fb_config;
	win->window = window;
	win->glx_window = glx_window;
	win->callbacks = *callbacks;

	register_glwin(win);
	if (win->callbacks.on_create)
		win->callbacks.on_create(win);
	return win;
}

void glwin_manager_make_current(struct glwin *win, GLXContext context)
{
	glXMakeContextCurrent(g_display, win->glx_window, win->glx_window, context);
}

GLXContext glwin_create_context(struct glwin *win, int maj_ver, int min_ver)
{
	int attribList[] = {
		GLX_CONTEXT_MAJOR_VERSION_ARB, maj_ver,
		GLX_CONTEXT_MINOR_VERSION_ARB, min_ver,
		GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};
	GLXContext context = glXCreateContextAttribsARB(g_display, win->fb_config, 0, 1, attribList);
	glXMakeContextCurrent(g_display, win->glx_window, win->glx_window, context);
	bool success = glb_glcore_init(maj_ver, min_ver);
	if (!success) {
		glXDestroyContext(g_display, context);
		context = 0;
	}
	return context;
}

static Bool match_any_event(Display *display, XEvent *event, XPointer arg)
{
	return True;
}

bool glwin_manager_process_events()
{
	XEvent event;
	int i;
	for (i = 0; i < g_event_count; i++) {
		int fd = g_events[i].data.fd;
		struct glwin *win = g_fd_binding[fd];
		if (win)
			if (win->callbacks.on_fd_event)
				win->callbacks.on_fd_event(win, fd, g_events[i].events);
	}
	g_event_count = 0;

	while (XCheckIfEvent(g_display, &event, match_any_event, NULL) == True) {
		struct glwin *win = find_glwin(event.xany.window);
		if (win)
			handle_x_event(win, &event);
	}
	return g_glwin_count > 0;
}

void glwin_swap_buffers(struct glwin *win)
{
	glXSwapBuffers(g_display, win->glx_window);
	XSync(g_display, 0);
}

int glwin_manager_wait_events()
{
	if (!g_event_count)
		g_event_count = epoll_wait(g_epoll_fd, g_events, 100, -1);
	if (g_event_count == -1) {
		fprintf(stderr, "glwin_manager_wait_events() epoll_wait failed: %s", strerror(errno));
		g_event_count = 0;
		return -1;
	} else {
		return 0;
	}
}

void glwin_manager_destroy_window(struct glwin *win)
{
	glXMakeContextCurrent(g_display, None, None, NULL);
	glXDestroyWindow(g_display, win->glx_window);
	XSync(g_display, 0);
	XDestroyWindow(g_display, win->window);
	retire_glwin(win);
}

void glwin_manager_fd_bind(int fd, struct glwin *win)
{
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
	ev.data.fd = fd;
	epoll_ctl(g_epoll_fd, EPOLL_CTL_ADD, fd, &ev);
	g_fd_binding[fd] = win;
}

void glwin_manager_fd_unbind(int fd)
{
	epoll_ctl(g_epoll_fd, EPOLL_CTL_DEL, fd, NULL);
	g_fd_binding[fd] = NULL;
}

void glwin_show_window(struct glwin *win)
{
	XMapWindow(g_display, win->window);
	XSync(g_display, 0);
}
