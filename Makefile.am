AM_CPPFLAGS = -I$(top_builddir)
ACLOCAL_AMFLAGS=-I m4

lib_LTLIBRARIES = libglwin.la
libglwin_la_SOURCES = glwin.c glb-glx.c
libglwin_la_LIBADD = $(GLB_GLCORE_LIBS)
libglwin_la_CFLAGS = $(GLB_GLCORE_CFLAGS)

noinst_PROGRAMS = example
example_SOURCES = example.c
example_LDADD = libglwin.la

BUILT_SOURCES = glb-glx.c glb-glx.h
CLEANFILES = glb-glx.c glb-glx.h

$(BUILT_SOURCES):
	glbindify -a glx

include_HEADERS = glwin.h glb-glx.h

pkgconfigdir = ${libdir}/pkgconfig
pkgconfig_DATA = glwin.pc
