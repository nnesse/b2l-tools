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
	/* index into typeface */
	int typeface_index;

	char c;

	/* Position of left edge of glyph */
	int left;

	/* Position of top of glyph (up is positive) */
	int top;

	/*
	 How much a space in the x-axis there should be between the start of this
	 glyph and the next
	*/
	int advance_x;

	/*
	 How much a space in the y-axis there should be between the start of this
	 glyph and the next
	*/
	int advance_y;

	/* coordinate in texture atlas */
	int w;

	gltext_font_t font;

	/* Glyph bitmap */
	int bitmap_width;
	int bitmap_height;
	int bitmap_pitch;
	uint8_t *bitmap_bits;
};

struct gltext_color {
	float r;
	float g;
	float b;
	float a;
};

struct gltext_glyph_instance {
	/* Position in pixels */
	float pos[2];

	/* Layer in texture array */
	int w;

	/* Color of glyph */
	struct gltext_color color;
};

//
// font
//
struct gltext_font {
	int size;
	gltext_typeface_t typeface;
	struct gltext_glyph *glyph_array;
	gltext_renderer_t renderer;
	int total_glyphs;
	uint32_t atlas_texture;
	uint32_t glyph_size_texture;
	uint32_t glyph_size_texture_buffer;
	uint8_t *atlas_buffer;
};

float gltext_get_advance(const struct gltext_glyph *prev, const struct gltext_glyph *next);

gltext_typeface_t gltext_renderer_get_typeface(gltext_renderer_t renderer, const char *path);

gltext_renderer_t gltext_renderer_new(const char *charset);
void gltext_renderer_free(gltext_renderer_t renderer);

gltext_font_t gltext_font_create(gltext_renderer_t renderer, gltext_typeface_t typeface, int font_size);

bool gltext_font_free(gltext_font_t font);

inline struct gltext_glyph *gltext_get_glyph(gltext_font_t font_, char c)
{
	struct gltext_font *font = (struct gltext_font *)(font_);
	return font->glyph_array + c;
}

struct gltext_glyph_instance *gltext_renderer_prepare_render(gltext_renderer_t renderer, gltext_font_t font, int num_chars);
void gltext_renderer_submit_render(gltext_renderer_t renderer, const struct gltext_color *color, const float *mvp);

#endif
