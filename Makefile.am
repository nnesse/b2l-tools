AM_CPPFLAGS = -I$(top_builddir)

lib_LTLIBRARIES = libglplatform.la
libglplatform_la_SOURCES = glplatform-linux.c glplatform-glcore.c glplatform-glx.c

noinst_PROGRAMS = example
example_SOURCES = example.c
example_LDADD = libglplatform.la

include_HEADERS = glplatform-glcore.h glplatform-glx.h glplatform.h
