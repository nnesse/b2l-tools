#
# Link with freetype2 and glfw staticly and enable GLBINDIFY support with gltext
#

all: simple

GLLOADER?=glew

VPATH = ..
CPPFLAGS = -I../ -I.
EXT_OBJS =

CXXFLAGS = -g -std=c++11 $(shell pkg-config glfw3 --static --cflags)
CXXFLAGS += $(shell pkg-config freetype2 --static --cflags)
LIBS = $(shell pkg-config glfw3 --static --libs)
LIBS += $(shell pkg-config freetype2 --static --libs)

ifeq ($(GLLOADER),glew)
CPPFLAGS+= -DGLTEXT_USE_GLEW=1
CXXFLAGS += $(shell pkg-config glew --static --cflags)
LIBS += $(shell pkg-config glew --static --libs)
else
ifeq ($(GLLOADER),glbindify)
CPPFLAGS+= -DGLTEXT_USE_GLBINDIFY=1
#
# Generate OpenGL 3.3 bindings with glbindify
#
gl_3_3.cpp gl_3_3.hpp:
	glbindify -a gl -v 3.3 \
		-e EXT_direct_state_access \
		-e ARB_multi_bind \
		-e ARB_vertex_attrib_binding \
		-e ARB_buffer_storage \
		-e ARB_texture_storage
gltext.o: gl_3_3.cpp gl_3_3.hpp
EXT_OBJS += gl_3_3.o
endif
endif

#
# Build examples using implicit rules to build gltext and bindings
#
simple: simple.cpp $(EXT_OBJS) gltext.o
	g++ -std=c++11 $(CPPFLAGS) $(CXXFLAGS) $< gltext.o $(EXT_OBJS) $(LIBS) -o $@

clean:
	@rm -f *.o gl_3_3.* simple
