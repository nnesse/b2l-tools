#ifndef GLTEXT_H
#define GLTEXT_H

#include <stdint.h>
#include <stdbool.h>

typedef void *gltext_renderer_t;
typedef void *gltext_typeface_t;
typedef void *gltext_font_t;

struct gltext_font;

//
// glyph
//
struct gltext_glyph {
	/* ASCII character of glyph */
	char c;

	/* Position of left edge of glyph */
	int left;

	/* Position of top of glyph (up is positive) */
	int top;

	/*
	 How much a space in the x-axis there should be between the start of this
	 glyph and the next glyph. This is a baseline value, for proper kerning
	 use gltext_get_advance()
	*/
	int advance_x;

	/*
	 How much a space in the y-axis there should be between the start of this
	 glyph and the next glyph
	*/
	int advance_y;

	/* Layer in texture array */
	int w;

	/* handle to font */
	gltext_font_t font;

	/* Glyph bitmap */
	int bitmap_width;
	int bitmap_height;
	int bitmap_pitch;
	uint8_t *bitmap_bits;

	/* Internal use only*/
	int typeface_index;
	bool valid;
};

struct gltext_color {
	float r;
	float g;
	float b;
	float a;
};

struct gltext_glyph_instance {
	/* (x,y) position in pixels */
	float pos[2];

	/* Layer in texture array */
	int w;
};

/*
 * gltext_get_advance()
 *
 * Returns the distance in the x direction that should be placed between two glyphs.
 */
float gltext_get_advance(const struct gltext_glyph *prev, const struct gltext_glyph *next);

/*
 * gltext_renderer_get_typeface()
 *
 * Returns an opaque handle to a TTF typeface given a path to the file.
 *
 */
gltext_typeface_t gltext_renderer_get_typeface(gltext_renderer_t renderer, const char *path);

/*
 * gltext_renderer_new()
 *
 * Returns an opaque handle to a text renderer that supports rendering characters in the array
 * 'charset'
 *
 */
gltext_renderer_t gltext_renderer_new(const char *charset);

/*
 * gltext_renderer_free()
 *
 * Free a previously created renderer.
 *
 */
void gltext_renderer_free(gltext_renderer_t renderer);

/*
 *
 * gltext_font_create()
 *
 * Create a font for a specific typeface.
 *
 */
gltext_font_t gltext_font_create(gltext_renderer_t renderer, gltext_typeface_t typeface, int font_size);


/*
 *
 * gltext_font_create_texture()
 *
 * Create a GL texture for the font. This can be done anytime after a font is created. Must be called
 * in a thread with a current OpenGL context. The GL_TEXTURE_2D_ARRAY and GL_TEXTURE_BUFFER bindings
 * are affected. The texture will be created automatically on the first render that specifies this font
 * if this call is not made.
 *
 */
void gltext_font_create_texture(gltext_font_t font);

/*
 *
 * gltext_font_destroy_texture()
 *
 * Destroy a previously created GL texture for the font. This can be done anytime after a font's texture
 * is created. Textures will automatically be destroyed when the font is free'd.
 *
 */
void gltext_font_destroy_texture(gltext_font_t font);

/*
 * gltext_font_free()
 *
 * Free a previously created font. Must be called with an available OpenGL context. Does not affect
 * any OpenGL state.
 *
 */
bool gltext_font_free(gltext_font_t font);

/*
 * gltext_get_glyph()
 *
 * Returns a pointer to gltext_glyph structure for a specific character. The returned structure
 * does not need to be deallocated and will be valid until the font is destroyed. If the character is not in
 * the renderer's charset the return value will be NULL.
 *
 */
const struct gltext_glyph *gltext_get_glyph(gltext_font_t font_, char c);

/*
 * gltext_renderer_prepare_render()
 *
 * Returns an array of uninitialized gltext_glyph_instance structures. After the values are filled
 * out by the application the glyphs can be rendered using gltext_renderer_submit_render(). The
 * positions of the glyphs can be computed by using gltext_get_advance(). The 'w' texture layer
 * field values should be taken from the 'w' field of the supplied font's associated gltext_glyph
 * structures. Undefined behavior will result if gltext_renderer_prepare_render() is called more
 * than once before calling gltext_renderer_submit_render().
 */
 struct gltext_glyph_instance *gltext_renderer_prepare_render(gltext_renderer_t renderer, gltext_font_t font, int num_chars);

 /*
  * gltext_renderer_submit_render()
  *
  * Render glyphs instances previously returned by gltext_renderer_prepare_render().
  *
  * color - RGBA color to render glyphs
  *
  * mvp - 4x4 column order "Model-View-Proection" matrix to position the glyphs.
  *
  * To position a glyph at (0,0) to window coordinate (x,y) you would use the mvp
  * matrix where (width, height) is the dimentions of the display:
  *
  * {2.0/width          , 0,                 ,0 ,0,
  *  0                  , 2.0/height         ,0 ,0,
  *  0                  , 1,                 ,1 ,0,
  * -1 + (x*2.0/width)  ,-1 + (y*2.0/height) ,0 ,1};
  *
  * The mvp transform can scale or rotate the text or contain a perspective transform
  * with limited text distortion thanks to the use is signed distance field texture maps.
  * Small font sizes display best when aligned to exact window coordinates
  * with integral glyph positions.
  */
 void gltext_renderer_submit_render(gltext_renderer_t renderer, const struct gltext_color *color, const float *mvp);

#endif
