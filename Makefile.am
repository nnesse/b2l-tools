AM_CPPFLAGS = -I$(top_builddir)

lib_LTLIBRARIES = libglplatform.la
libglplatform_la_SOURCES = glplatform.c glplatform-glcore.c glplatform-glx.c

noinst_PROGRAMS = example
example_SOURCES = example.c
example_LDADD = libglplatform.la

BUILT_SOURCES = glplatform-glcore.c glplatform-glx.c
CLEANFILES = $(BUILT_SOURCES) glplatform-glx.h glplatform-glcore.h

glplatform-glcore.c:
	$(GLBINDIFY) -a gl -n glplatform

glplatform-glx.c:
	$(GLBINDIFY) -a glx -n glplatform

include_HEADERS = glplatform-glcore.h glplatform-glx.h glplatform.h
