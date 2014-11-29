#
# Link with freetype2 and glfw staticly and enable GLBINDIFY support with gltext
#

all: simple terminal

GLLOADER?=glew

VPATH = ..
CPPFLAGS = -I../ -I.
EXT_OBJS =

CXXFLAGS = -g -std=c++11 $(shell pkg-config glfw3 --static --cflags)
CXXFLAGS += $(shell pkg-config freetype2 --static --cflags)
LIBS = $(shell pkg-config glfw3 --static --libs)
LIBS += $(shell pkg-config freetype2 --static --libs)


OBJS = gltext.o

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
gltext.o: gl_3_3.cpp gl_3_3.hpp gltext.hpp
OBJS += gl_3_3.o
endif
endif

gltext.o: gltext.cpp gltext.hpp

#
# Build examples using implicit rules to build gltext and bindings
#
text_stream: text_stream.cpp $(OBJS) gltext.hpp
	$(CXX) -std=c++11 $(CPPFLAGS) $(CXXFLAGS) $< $(OBJS) $(LIBS) -o $@

terminal: terminal.cpp $(OBJS) gltext.hpp
	$(CXX) -std=c++11 $(CPPFLAGS) $(CXXFLAGS) $< $(OBJS) $(LIBS) -o $@

clean:
	@rm -f *.o gl_3_3.* simple
