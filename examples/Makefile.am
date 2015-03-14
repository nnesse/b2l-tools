AM_CFLAGS = -std=c99
bin_PROGRAMS=simple
noinst_SOURCE=simple.c
simple_CPPFLAGS=-I${top_srcdir}
simple_CFLAGS=$(GLB_GLCORE_CFLAGS) $(GLWIN_CFLAGS)
simple_LDADD=$(GLB_GLCORE_LIBS) $(GLWIN_LIBS) ../libgltext.la
