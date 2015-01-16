#ifndef GLTEXT_H
#define GLTEXT_H

#if defined(__cplusplus)
extern "C" {

#else

#include <stdbool.h>

#endif

#include <stdint.h>

typedef void *gl_text__renderer_t;
typedef void *gl_text__typeface_t;

struct gl_text__font;

//
// glyph
//
struct gl_text__glyph {
	/* index into typeface */
	int typeface_index;

	char c;

	/* index into atlas */
	int atlas_index;

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

	/* Position of the glyph in 3D texture */
	int u;
	int v;
	int w;

	const struct gl_text__font *font;

	/* Glyph bitmap */
	int bitmap_width;
	int bitmap_height;
	int bitmap_pitch;
	uint8_t *bitmap_bits;

	/*
	glyph() :
		typeface_index(-1),
		atlas_index(-1),
		left(0), top(0),
		advance_x(0), advance_y(0),
		u(0), v(0), w(0),
		width(0), height(0),pitch(0) {}
	*/
};

struct gl_text__color {
	float r;
	float g;
	float b;
	float a;
};

struct gl_text__glyph_instance {
	/* Position in pixels */
	float pos[2];

	/* Atlas index for GPU lookup */
	int atlas_index;

	/* Color of glyph */
	struct gl_text__color color;
};

//
// font
//
struct gl_text__font {
	int width;
	int height;
	gl_text__typeface_t typeface;
	struct gl_text__glyph *glyph_array;
	const char *family;
	int style;
	gl_text__renderer_t renderer;
};

//
// font desc
//
struct gl_text__font_desc {
	gl_text__typeface_t typeface;
	const char *family;
	int style;
	int width;
	int height;
	const char *charset;
};

int gl_text__get_advance(const struct gl_text__glyph *prev, const struct gl_text__glyph *next); //*

gl_text__typeface_t gl_text__renderer__get_typeface(gl_text__renderer_t renderer, const char *path); //*

gl_text__renderer_t  gl_text__renderer__create(); //*
void gl_text__renderer__free(gl_text__renderer_t renderer); //*

bool gl_text__renderer__initialize(gl_text__renderer_t renderer,
	const struct gl_text__font_desc *font_descriptions,
	int count,
	const struct gl_text__font **fonts);

struct gl_text__glyph_instance *gl_text__renderer__prepare_render(gl_text__renderer_t renderer, int num_chars); //*
void gl_text__renderer__submit_render(gl_text__renderer_t renderer, const float *mvp); //*
void gl_text__renderer__set_ambient_color(gl_text__renderer_t renderer, struct gl_text__color *color); //*

#if defined(__cplusplus)
}
#endif

#endif
