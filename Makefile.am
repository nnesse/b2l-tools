AM_CPPFLAGS = -I$(top_builddir)

lib_LTLIBRARIES = libglwin.la
libglwin_la_SOURCES = glwin.c glb-glx.c
libglwin_la_LIBADD = -lX11 -lGL
libglwin_la_CFLAGS =

noinst_PROGRAMS = example
example_SOURCES = example.c
example_LDADD = libglwin.la -lglb-glcore

BUILT_SOURCES = glb-glx.c glb-glx.h
CLEANFILES = glb-glx.c glb-glx.h

$(BUILT_SOURCES):
	glbindify -a glx

include_HEADERS = glwin.h glb-glx.h
