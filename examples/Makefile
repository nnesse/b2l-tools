#
# Link with freetype2 and glfw staticly and enable GLBINDIFY support with gltext
#
VPATH = ..
CPPFLAGS = -I../ -I. -DGLTEXT_USE_GLBINDIFY=1
CXXFLAGS = -std=c++11 $(shell pkg-config glfw3 --static --cflags) $(shell pkg-config freetype2 --static --cflags)
LIBS = $(shell pkg-config glfw3 --static --libs) $(shell pkg-config freetype2 --static --libs)

all: simple

#
# Generate OpenGL 3.3 bindings with glbindify
#
gl_3_3.cpp gl_3_3.hpp:
	glbindify -a gl -v 3.3 \
		-e EXT_direct_state_access \
		-e ARB_multi_bind \
		-e ARB_vertex_attrib_binding \
		-e ARB_buffer_storage \
		-e EXT_texture_filter_anisotropic \
		-e ARB_texture_storage

#
# Build examples using implicit rules to build gltext and bindings
#
simple: simple.cpp gl_3_3.o gltext.o 
	g++ -std=c++11 $(CPPFLAGS) $(CXXFLAGS) $< gltext.o gl_3_3.o $(LIBS) -o $@

clean:
	@rm -f *.o gl_3_3.* simple
