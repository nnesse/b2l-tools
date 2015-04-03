AM_CPPFLAGS = -I$(top_builddir)

lib_LTLIBRARIES = libglwin.la
libglwin_la_SOURCES = glwin.c
libglwin_la_LIBADD = -lX11 -lGL -lglb-glx
libglwin_la_CFLAGS =

noinst_PROGRAMS = example
example_SOURCES = example.c
example_LDADD = libglwin.la -lglb-glcore

include_HEADERS = glwin.h
