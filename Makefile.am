AM_CPPFLAGS = -I$(top_srcdir)/include \
	      -I$(top_srcdir)/include/math \
	      -I$(top_srcdir)/include/glbindings

lib_LTLIBRARIES = libglplatform.la
libglplatform_la_SOURCES = src/glplatform-linux.c \
			   src/glbindings/glplatform-glcore.c \
			   src/glbindings/glplatform-glx.c \
			   src/math/math3d.c

noinst_PROGRAMS = example
example_SOURCES = src/examples/example.c
example_LDADD = libglplatform.la

pkginclude_HEADERS = include/glbindings/glplatform-glcore.h \
		     include/glbindings/glplatform-glx.h \
		     include/glplatform.h \
		     include/math/math3d.h
