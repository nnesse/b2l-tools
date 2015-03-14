ACLOCAL_AMFLAGS=-I m4

lib_LTLIBRARIES=libgltext.la
libgltext_la_SOURCES=gltext.c
libgltext_la_LIBADD=$(GLB_GLCORE_LIBS) $(FREETYPE2_LIBS)
libgltext_la_CFLAGS=-std=c99 $(GLB_GLCORE_CFLAGS) $(FREETYPE2_CFLAGS)

SUBDIRS=. examples

include_HEADERS=gltext.h

pkgconfigdir = ${libdir}/pkgconfig
pkgconfig_DATA = gltext.pc
