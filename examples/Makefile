#
# Link with freetype2 and glfw staticly and enable GLBINDIFY support with gltext
#

all: simple

VPATH = ..
CPPFLAGS = -I../ -I.

CFLAGS := -Wall -Werror -std=c99 -g -O0
CFLAGS += $(shell pkg-config glfw3 --cflags)
CFLAGS += $(shell pkg-config freetype2 --cflags)
CFLAGS += $(shell pkg-config glb-glcore--cflags)
LIBS = $(shell pkg-config glfw3 --libs)
LIBS += $(shell pkg-config freetype2 --libs)
LIBS += $(shell pkg-config glb-glcore --libs)

OBJS = gltext.o

gltext.o: gltext.c gltext.h

#
# Build examples using implicit rules to build gltext and bindings
#
simple: simple.c $(OBJS) gltext.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(OBJS) $(LIBS) -o $@

clean:
	@rm -f *.o simple
