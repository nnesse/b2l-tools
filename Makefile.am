AM_CPPFLAGS = -I$(top_builddir)

lib_LTLIBRARIES = libglplatform.la
libglplatform_la_SOURCES = glwin.c glb-glcore.c glb-glx.c

noinst_PROGRAMS = example
example_SOURCES = example.c
example_LDADD = libglplatform.la

BUILT_SOURCES = glb-glcore.c glb-glx.c
CLEANFILES = $(BUILT_SOURCES) glb-glx.h glb-glcore.h

glb-glcore.c:
	$(GLBINDIFY) -a gl

glb-glx.c:
	$(GLBINDIFY) -a glx

include_HEADERS = glb-glcore.h glb-glx.h glplatform.h
