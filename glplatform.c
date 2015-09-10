#include "glplatform.h"

#ifndef _WIN32
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <sys/epoll.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define GLPLATFORM_ENABLE_GLX_ARB_create_context
#define GLPLATFORM_ENABLE_GLX_ARB_create_context_profile
#include "glplatform-glx.h"

int glplatform_epoll_fd;

static int g_x11_fd;
static int g_event_count;
static struct epoll_event g_events[100];
static Display *g_display;
static int g_screen;
static Atom g_delete_atom;
static int g_max_fd = 0;
#else

#define GLPLATFORM_ENABLE_WGL_ARB_create_context
#define GLPLATFORM_ENABLE_WGL_ARB_create_context_profile
#include "glplatform-wgl.h"
#endif

static struct glplatform_win *g_win_list = NULL;
static int g_glplatform_win_count = 0;

struct fd_binding {
	struct glplatform_win *win;
	intptr_t user_data;
};

static struct fd_binding *g_fd_binding;

#ifndef _WIN32
static struct glplatform_win *find_glplatform_win(Window w)
#else
static struct glplatform_win *find_glplatform_win(HWND hwnd)
#endif
{
	struct glplatform_win *win = g_win_list;
	while (win) {
#ifndef _WIN32
		if (win->window == w)
#else
		if (win->hwnd == hwnd)
#endif
			return win;
		win = win->next;
	}
	return NULL;
}

static void retire_glplatform_win(struct glplatform_win *win)
{
	struct glplatform_win *pos = g_win_list;
	while (win) {
		if (pos == win) {
			*(pos->pprev) = pos->next;
			if (pos->next)
				pos->next->pprev = pos->pprev;
			g_glplatform_win_count--;
			break;
		}
		pos = pos->next;
	}

#ifndef _WIN32
	//Note: This is ineffient but we shouldn't be
	//destroying windows very often.
	int i;
	for (i = 0; i < g_max_fd; i++) {
		if (g_fd_binding[i].win == win) {
			glplatform_fd_unbind(i);
		}
	}
#endif
}

static void register_glplatform_win(struct glplatform_win *win)
{
#ifdef _WIN32
	struct glplatform_win *test = find_glplatform_win(win->hwnd);
#else
	struct glplatform_win *test = find_glplatform_win(win->window);
#endif
	if (test)
		return;
	g_glplatform_win_count++;
	win->next = g_win_list;
	win->pprev = &g_win_list;
	g_win_list = win;
}

static void on_mouse_wheel(struct glplatform_win *win, int x, int y, int a)
{
	if (win->callbacks.on_mouse_wheel)
		win->callbacks.on_mouse_wheel(win, x, y, a);
}

#ifndef _WIN32
bool glplatform_is_button_pressed(struct glplatform_win *win, int button)
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

bool glplatform_is_shift_pressed(struct glplatform_win *win)
{
	return win->x_state_mask & ShiftMask;
}

bool glplatform_is_control_pressed(struct glplatform_win *win)
{
	return win->x_state_mask & ControlMask;
}

static int handle_x_event(struct glplatform_win *win, XEvent *event)
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
			if(win->callbacks.on_expose)
				win->callbacks.on_expose(win);
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
		win->callbacks.on_x_event(win, event);
	return 0;
}
#endif

bool glplatform_init()
{
#ifdef _WIN32
	glplatform_wgl_init(1, 0);
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = PlatformWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = 0;
	wc.lpszClassName = "glplatform";
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;

	if (RegisterClassEx(&wc) == 0) {
		return false;
	}
#else
	g_event_count = 0;
	glplatform_epoll_fd = epoll_create1(0);
	g_display = XOpenDisplay(NULL);
	g_x11_fd = XConnectionNumber(g_display);
	glplatform_glx_init(1, 4);

	struct rlimit rl;
	int rc = getrlimit(RLIMIT_NOFILE, &rl);
	if (rc)
		return false;

	g_max_fd = rl.rlim_max;
	g_fd_binding = (struct fd_binding *)calloc(rl.rlim_max, sizeof(struct fd_binding));
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = g_x11_fd;
	epoll_ctl(glplatform_epoll_fd, EPOLL_CTL_ADD, g_x11_fd, &ev); //TODO: check for errors

	g_screen = DefaultScreen(g_display);
	g_delete_atom = XInternAtom(g_display, "WM_DELETE_WINDOW", True);
	return true;
#endif
}

void glplatform_shutdown()
{
#ifndef _WIN32
	XCloseDisplay(g_display);
#endif
}

#ifdef _WIN32

static LRESULT CALLBACK windows_event(struct glplatform_win *win, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

static LRESULT CALLBACK PlatformWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	struct glplatform_win *win;
	if (Msg == WM_CREATE) {
		CREATESTRUCT *cs = (CREATESTRUCT *) lParam;
		win = (struct glplatform_win *)cs->lpCreateParams;
		SetWindowLongPtr(hWnd, -21/* GLW_USERDATA */, (LONG_PTR)win);
	} else {
		win = (struct glplatform_win *)GetWindowLongPtr(hWnd, -21 /* GLW_USERDATA */);
	}

	if (win) {
		return windows_event(win, hWnd, Msg, wParam, lParam);
	} else {
		return DefWindowProc(hWnd, Msg, wParam, lParam);;
	}
}

static LRESULT CALLBACK windows_event(struct glplatform_win *win, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	RECT cr;

	GetClientRect(hWnd, &cr);

	switch (Msg) {
	case WM_PAINT: {
		//on_redraw();
		ValidateRect(hWnd, NULL);
	} break;
	case WM_SIZE:{
		int width = LOWORD(lParam);
		int height = HIWORD(lParam);
	} break;
	case WM_CREATE:{
		int width = cr.right;
		int height = cr.bottom;
		win->hdc = GetDC(hWnd);
		win->hwnd = hWnd;
		static PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW |		//window drawing support
			PFD_SUPPORT_OPENGL |	//opengl support
			PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = win->fbformat.color_bits;
		pfd.cAlphaBits = win->fbformat.alpha_bits;
		pfd.cStencilBits = win->fbformat.stencil_bits;
		pfd.cAccumBits = win->fbformat.accum_bits;
		pfd.cDepthBits = win->fbformat.depth_bits;

		win->pixel_format = ChoosePixelFormat(win->hdc, &pfd);
		if (win->pixel_format == 0) {
			return -1;
		}
		if (SetPixelFormat(win->hdc, win->pixel_format, &pfd) == FALSE) {
			return -1;
		}
	} break;
	case WM_KEYDOWN:{
		WPARAM key = wParam;
	} break;
	case WM_KEYUP:{
		WPARAM key = wParam;
	} break;
	case WM_LBUTTONDOWN:{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
	} break;
	case WM_LBUTTONUP:{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
	} break;
	case WM_RBUTTONDOWN:{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
	} break;
	case WM_RBUTTONUP:{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
	} break;
	case WM_MOUSEMOVE:{
		ShowCursor(FALSE);
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		int lbutton_down = wParam & MK_LBUTTON;
	        int rbutton_down = wParam & MK_RBUTTON;
	} break;
	case WM_MOUSEWHEEL:{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		int delta = GET_WHEEL_DELTA_WPARAM(wParam);
	} break;
	case WM_CLOSE:{
	} break;
	case WM_DESTROY:{
		//PostQuitMessage(0);
	} break;
	default:{
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	} break;
	}
	return 0;
}
#endif

struct glplatform_win *glplatform_create_window(const char *title,
		const struct glplatform_win_callbacks *callbacks,
		const struct glplatform_fbformat *fbformat,
		int width, int height)
{
	static struct glplatform_fbformat default_fbformat = {
		.color_bits = 24,
		.alpha_bits = 8,
		.stencil_bits = 8,
		.depth_bits = 24,
		.accum_bits = 0
	};

	if (fbformat == NULL) {
		fbformat = &default_fbformat;
	}

	if (fbformat->color_bits % 3)
		return NULL;

	struct glplatform_win *win = (struct glplatform_win *) malloc(sizeof(struct glplatform_win));
	win->fbformat = *fbformat;
	win->callbacks = *callbacks;

#ifdef _WIN32
	RECT wr = { 0, 0, width, height };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hwnd = CreateWindow("glplatform",
				 title,
				 WS_OVERLAPPEDWINDOW,
				 CW_USEDEFAULT,
				 CW_USEDEFAULT,
				 wr.right - wr.left,
				 wr.bottom - wr.top,
				 NULL,
				 NULL,
				 0,
				 win);

	if (hwnd == NULL) {
		free(win);
		return NULL;
	}
#else
	GLXFBConfig fb_config;
	Window window;
	GLXWindow glx_window;

	int fb_attributes[] = {
		/* attribute/value pairs */
		GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
		GLX_RENDER_TYPE, GLX_RGBA_BIT,
		GLX_DOUBLEBUFFER, 1,
		GLX_RED_SIZE, fbformat->color_bits / 3,
		GLX_GREEN_SIZE, fbformat->color_bits / 3,
		GLX_BLUE_SIZE, fbformat->color_bits / 3,
		GLX_ALPHA_SIZE, fbformat->alpha_bits,
		GLX_STENCIL_SIZE, fbformat->stencil_bits,
		GLX_DEPTH_SIZE, fbformat->depth_bits,
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

	win->width = width;
	win->height = height;
	win->fb_config = fb_config;
	win->window = window;
	win->glx_window = glx_window;
#endif
	register_glplatform_win(win);
	if (win->callbacks.on_create)
		win->callbacks.on_create(win);

	return win;
}

#ifndef _WIN32
void glplatform_set_win_transient_for(struct glplatform_win *win, intptr_t id)
{
	XSetTransientForHint(g_display, win->window, id);
}

void glplatform_set_win_type(struct glplatform_win *win, enum glplatform_win_types type)
{
	Atom type_atom = 0;
	switch (type) {
	case GLWIN_POPUP:
		type_atom = XInternAtom(g_display, "_NET_WM_WINDOW_TYPE_POPUP_MENU", False);
		break;
	case GLWIN_NORMAL:
		type_atom = XInternAtom(g_display, "_NET_WM_WINDOW_TYPE_NORMAL", False);
		break;
	case GLWIN_DIALOG:
		type_atom = XInternAtom(g_display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
		break;
	case GLWIN_TOOLBAR:
		type_atom = XInternAtom(g_display, "_NET_WM_WINDOW_TYPE_TOOLBAR", False);
		break;
	case GLWIN_UTILITY:
		type_atom = XInternAtom(g_display, "_NET_WM_WINDOW_TYPE_UTILITY", False);
		break;
	default:
		return;
	}
	XChangeProperty(g_display,
		win->window,
		XInternAtom(g_display, "_NET_WM_WINDOW_TYPE", False),
		XA_ATOM,
		32,
		PropModeReplace,
		(const unsigned char *)&type_atom,
		1);
}
#endif

void glplatform_make_current(struct glplatform_win *win, glplatform_gl_context_t context)
{
#ifdef _WIN32
	wglMakeCurrent(win->hdc, (HGLRC)context);
#else
	glXMakeContextCurrent(g_display, win->glx_window, win->glx_window, (void *)context);
#endif
}

glplatform_gl_context_t glplatform_create_context(struct glplatform_win *win, int maj_ver, int min_ver)
{
#ifdef _WIN32
	int attribList[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, maj_ver,
		WGL_CONTEXT_MINOR_VERSION_ARB, min_ver,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
		0
	};

	HGLRC rc = wglCreateContextAttribsARB(win->hdc, 0, attribList);
	return rc;
#else
	int attribList[] = {
		GLX_CONTEXT_MAJOR_VERSION_ARB, maj_ver,
		GLX_CONTEXT_MINOR_VERSION_ARB, min_ver,
		GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};
	return (glplatform_gl_context_t)glXCreateContextAttribsARB(g_display, win->fb_config, 0, 1, attribList);
#endif
}

#ifndef _WIN32
void glplatform_fullscreen_win(struct glplatform_win *win, bool fullscreen)
{
	XWindowAttributes attr;
	bool mapped;

	Atom net_wm_state = XInternAtom(g_display, "_NET_WM_STATE", False);
	Atom net_wm_state_fullscreen = XInternAtom(g_display, "_NET_WM_STATE_FULLSCREEN", False);

	XGetWindowAttributes(g_display, win->window, &attr);
	mapped = (attr.map_state == IsUnmapped) ? false : true;

	if (mapped) {
		XEvent e;
		e.xany.type = ClientMessage;
		e.xclient.message_type = net_wm_state;
		e.xclient.format = 32;
		e.xclient.window = win->window;
		e.xclient.data.l[0] = fullscreen ? 1 : 0;
		e.xclient.data.l[1] = net_wm_state_fullscreen;
		e.xclient.data.l[3] = 0;
		XSendEvent(g_display,
				RootWindow(g_display, g_screen),
				0,
				SubstructureNotifyMask |
				SubstructureRedirectMask, &e);
		XFlush(g_display);

	} else {
		Atom atoms[2] = {
			net_wm_state_fullscreen,
			None
		};
		XChangeProperty(g_display,
			win->window,
			net_wm_state,
			XA_ATOM,
			32,
			PropModeReplace,
			(const unsigned char *)atoms,
			fullscreen ? 1 : 0);
	}
}

static Bool match_any_event(Display *display, XEvent *event, XPointer arg)
{
	return True;
}
#endif

int glplatform_get_events(bool block)
{
#ifdef _WIN32
	if (block) {
		if (WaitMessage()) {
			return -1;
		} else {
			return 1;
		}
	} else {
		MSG Msg;
		return PeekMessage(&Msg, NULL, 0, 0, PM_NOREMOVE);
	}
#else
	int rc = 0;
	if (g_event_count < 100) {
		rc = epoll_wait(glplatform_epoll_fd, g_events + g_event_count, 100 - g_event_count, block ? -1 : 0);
		if (rc == -1) {
			fprintf(stderr, "glplatform_get_events(): epoll_wait() failed: %s", strerror(errno));
		} else {
			g_event_count += rc;
		}
	}
	return rc;
#endif
}

bool glplatform_process_events()
{
#ifdef _WIN32
	MSG Msg;
	while (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) {
		if (Msg.message == WM_QUIT) {
			return false;
		}
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
#else
	XEvent event;
	int i;
	for (i = 0; i < g_event_count; i++) {
		int fd = g_events[i].data.fd;
		struct glplatform_win *win = g_fd_binding[fd].win;
		if (win)
			if (win->callbacks.on_fd_event)
				win->callbacks.on_fd_event(win, fd, g_events[i].events, g_fd_binding[fd].user_data);
	}
	g_event_count = 0;

	while (XCheckIfEvent(g_display, &event, match_any_event, NULL) == True) {
		struct glplatform_win *win = find_glplatform_win(event.xany.window);
		if (win)
			handle_x_event(win, &event);
	}
#endif
	return g_glplatform_win_count > 0;
}

void glplatform_swap_buffers(struct glplatform_win *win)
{
#ifdef _WIN32
	SwapBuffers(win->hdc);
#else
	glXSwapBuffers(g_display, win->glx_window);
	XSync(g_display, 0);
#endif
}

void glplatform_destroy_window(struct glplatform_win *win)
{
#ifdef _WIN32
	wglMakeCurrent(win->hdc, 0);
	DestroyWindow(win->hwnd);
#else
	glXMakeContextCurrent(g_display, None, None, NULL);
	glXDestroyWindow(g_display, win->glx_window);
	XSync(g_display, 0);
	XDestroyWindow(g_display, win->window);
#endif
	retire_glplatform_win(win);
	free(win);
}

#ifndef _WIN32
void glplatform_fd_bind(int fd, struct glplatform_win *win, intptr_t user_data)
{
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
	ev.data.fd = fd;
	epoll_ctl(glplatform_epoll_fd, EPOLL_CTL_ADD, fd, &ev);
	g_fd_binding[fd].win = win;
	g_fd_binding[fd].user_data = user_data;
}

void glplatform_fd_unbind(int fd)
{
	epoll_ctl(glplatform_epoll_fd, EPOLL_CTL_DEL, fd, NULL);
	g_fd_binding[fd].win = NULL;
	g_fd_binding[fd].user_data = 0;
}
#endif

void glplatform_show_window(struct glplatform_win *win)
{
#ifdef _WIN32
	ShowWindow(win->hwnd, SW_SHOWNORMAL);
	UpdateWindow(win->hwnd);
#else
	XMapWindow(g_display, win->window);
	XSync(g_display, 0);
#endif
}

#ifndef _WIN32
void glplatform_get_thread_state(struct glplatform_thread_state *state)
{
	state->write_draw = glXGetCurrentDrawable();
	state->read_draw = glXGetCurrentDrawable();
	state->display = glXGetCurrentDisplay();
	state->context = glXGetCurrentContext();
}

void glplatform_set_thread_state(const struct glplatform_thread_state *state)
{
	glXMakeContextCurrent(state->display,
			state->write_draw,
			state->read_draw,
			state->context);
}
#endif
