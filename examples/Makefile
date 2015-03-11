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

glb_gl.c glb_gl.h:
	glbindify -a gl

glb_gl.o: glb_gl.c glb_gl.h
OBJS += glb_gl.o

gltext.o: gltext.c gltext.h glb_gl.h

#
# Build examples using implicit rules to build gltext and bindings
#
simple: simple.c $(OBJS) gltext.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(OBJS) $(LIBS) -o $@

clean:
	@rm -f *.o glb_gl.* simple
