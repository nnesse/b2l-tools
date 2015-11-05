AM_CPPFLAGS = -I$(top_srcdir)/include \
	      -I$(top_srcdir)/include/math \
	      -I$(top_srcdir)/include/glbindings

#if WITH_TEXT
AM_CPPFLAGS += -I$(top_srcdir)/include/text
#enif

lib_LTLIBRARIES = libglplatform.la
libglplatform_la_LIBADD=$(FREETYPE2_LIBS)
libglplatform_la_CFLAGS=-std=c99 $(FREETYPE2_CFLAGS)
libglplatform_la_SOURCES = src/glplatform-linux.c \
			   src/glbindings/glplatform-glcore.c \
			   src/glbindings/glplatform-glx.c \
			   src/math/math3d.c
if WITH_TEXT
libglplatform_la_SOURCES += src/text/gltext.c
endif

noinst_PROGRAMS = simple_window
if WITH_TEXT
noinst_PROGRAMS += text_render
endif

simple_window_SOURCES = src/examples/simple_window.c
simple_window_LDADD = libglplatform.la

text_render_SOURCES = src/examples/text_render.c
text_render_CFLAGS = -DTTF_PATH=\"${abs_srcdir}/src/examples/ttf/\"
text_render_LDADD = libglplatform.la

pkginclude_HEADERS = include/glbindings/glplatform-glcore.h \
		     include/glbindings/glplatform-glx.h \
		     include/glplatform.h \
		     include/math/math3d.h
if WITH_TEXT
pkginclude_HEADERS += include/text/gltext.h
endif
