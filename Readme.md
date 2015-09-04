gltext
======

gltext is a data driven text renderer for OpenGL 3.x based on libfreetype.
It can render transformed text with minimal distortion as well as render untransformed
text with high quality anti-aliasing. Its design focuses on simplicity, performance,
 and control.

To render text an application requests an array of glyph instance structures which
it fills in with glyph positions and glyph identifiers. Glyph metric and kerning
information that can be queried from the API to enable the application to solve layout
problems such as line breaking, centering, etc. Each render is submitted with a transform
4x4 transform matrix, enabing the text to be scaled and rotated in three dimentions. For
the more common case of rendering aligned text this matrix would only be used to scale
and translate the (x,y) the coordinates from pixels to normalized device coordinates.

Implementation
--------------

For each font `gltext` generates a signed distance field texture array and places one
glyph in each layer. While this is not optimal from a memory footprint standpoint it
should still be relative efficient for the GPU to process. It also allows texture filtering
to be used with minimal complexity. A geometry shader is used which directly consumes the
application generated glyph data, minimizing driver overhead.

Building
--------

`gltext` has an autotools build system which can be invoked with:

	./autogen.sh
	./configure
	make
	make install

`gltext` requires `libfreetype2` and `glplatform` to build successfully. Freetype
is used to generate the glyph bitmap's and metrics. glplatform is used to manage
OpenGL context bindings. It should be relatively trivial to port `gltext`
to different build systems and platform libraries if desired.
