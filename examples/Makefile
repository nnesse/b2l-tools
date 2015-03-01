#
# Link with freetype2 and glfw staticly and enable GLBINDIFY support with gltext
#

all: simple

VPATH = ..
CPPFLAGS = -I../ -I.
EXT_OBJS =

CFLAGS := -Wall -Werror
CFLAGS += $(shell pkg-config glfw3 --cflags)
CFLAGS += $(shell pkg-config freetype2 --cflags)
CFLAGS += -std=c99 -g -O0
LIBS = $(shell pkg-config glfw3 --libs)
LIBS += $(shell pkg-config freetype2 --libs)

OBJS = gltext.o

#
# Generate OpenGL 3.3 bindings with glbindify
#

gl_3_3.c gl_3_3.h:
	glbindify -l C -a gl -v 3.3 \
		-e EXT_direct_state_access \
		-e ARB_multi_bind \
		-e ARB_vertex_attrib_binding \
		-e ARB_buffer_storage \
		-e ARB_texture_storage

gl_3_3.o: gl_3_3.c gl_3_3.h
OBJS += gl_3_3.o

gltext_capi.o: gltext.c gltext.h

#
# Build examples using implicit rules to build gltext and bindings
#
simple: simple.c $(OBJS) gltext.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(OBJS) $(LIBS) -o $@

clean:
	@rm -f *.o gl_3_3.* simple
