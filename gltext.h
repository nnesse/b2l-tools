#ifndef GLTEXT_H
#define GLTEXT_H

#include <stdint.h>
#include <stdbool.h>

typedef void *gltext_renderer_t;
typedef void *gltext_typeface_t;

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

	/* layer texture atlas */
	int w;

	const struct gltext_font *font;

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
};

//
// font desc
//
struct gltext_font_desc {
	int size;
	gltext_typeface_t typeface;
};

float gltext_get_advance(const struct gltext_glyph *prev, const struct gltext_glyph *next);

gltext_typeface_t gltext_renderer_get_typeface(gltext_renderer_t renderer, const char *path);

gltext_renderer_t gltext_renderer_new();
void gltext_renderer_free(gltext_renderer_t renderer);

bool gltext_renderer_initialize(gltext_renderer_t renderer,
	const char *charset,
	const struct gltext_font_desc *font_descriptions,
	int count,
	struct gltext_font *fonts);

struct gltext_glyph_instance *gltext_renderer_prepare_render(gltext_renderer_t renderer, const struct gltext_font *font, int num_chars);
void gltext_renderer_submit_render(gltext_renderer_t renderer, const struct gltext_color *color, const float *mvp);

#endif
