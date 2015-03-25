ACLOCAL_AMFLAGS=-I m4

lib_LTLIBRARIES=libgltext.la
libgltext_la_SOURCES=gltext.c
libgltext_la_LIBADD=-lglb-glcore $(FREETYPE2_LIBS)
libgltext_la_CFLAGS=-std=c99 $(FREETYPE2_CFLAGS)

SUBDIRS=. examples

include_HEADERS=gltext.h
