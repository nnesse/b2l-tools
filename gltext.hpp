/*

Copyright (c) 2014 Neils Nesse

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#ifndef GLTEXT_HPP
#define GLTEXT_HPP

#if !GLTEXT_USE_GLBINDIFY && !GLTEXT_USE_GLEW
#define GLTEXT_USE_GLEW 1
#endif

#if GLTEXT_USE_GLEW
#include "GL/glew.h"
#elif GLTEXT_USE_GLBINDIFY
#include "gl_3_3.hpp"
using namespace glbindify;
#endif

#include <vector>
#include <unordered_map>

#include <vector>
#include <sstream>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace gl_text {
	class text_stream;
};

namespace std {
	gl_text::text_stream &endl(gl_text::text_stream &t);
};

namespace gl_text {

typedef FT_Face typeface_t;

enum halign {
	HALIGN_LEFT = -1,
	HALIGN_CENTER = 0,
	HALIGN_RIGHT = 1,
};

enum valign {
	VALIGN_TOP = -1,
	VALIGN_CENTER = 0,
	VALIGN_BOTTOM = 1,
};

enum font_style {
	STYLE_REGULAR = 0,
	STYLE_ITALIC = 1,
	STYLE_BOLD = 2,
};

class font;

//
// glyph
//
class glyph {
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

	const gl_text::font *font;

	/* Glyph bitmap */
	int width;
	int height;
	int pitch;

	std::vector<uint8_t> buffer;
	friend class renderer;
	friend class text;
	friend int gl_text::get_advance(const glyph *prev, const glyph *next);
public:
	glyph() : typeface_index(-1), atlas_index(-1), left(0), top(0), advance_x(0), advance_y(0), u(0), v(0), w(0), width(0), height(0), pitch(0) {}
	int get_left() const {
		return left;
	}
	int get_top() const {
		return top;
	}
	int get_width() const {
		return width;
	}
	int get_height() const {
		return height;
	}
	int get_advance() const {
		return advance_x;
	}
	int get_index() const {
		return atlas_index;
	}
};

class renderer;

//
// font
//
class font {
	int m_width;
	int m_height;
	typeface_t m_typeface;
	std::vector<glyph> m_glyphs;
	std::string m_family;
	int m_style;
	renderer *m_renderer;
	friend class renderer;
	friend class text;
	friend class text_stream;
	friend int get_advance(const glyph *prev, const glyph *next);
	void select() const;
public:
	font() {
		m_glyphs.resize(256);
	}
	const glyph &get_glyph(char c) const {
		return m_glyphs[c];
	}
	const std::string &family() const {
		return m_family;
	}
	int get_style() const {
		return m_style;
	}
	int get_height() const {
		return m_height;
	}
	int get_width() const {
		return m_width;
	}
	~font() { }
};

struct color {
	float r;
	float g;
	float b;
	float a;
	color(float r_, float g_, float b_, float a_) :
		r(r_),
		g(g_),
		b(b_),
		a(a_) { }
	color() { }
};

struct glyph_instance {
	float pos[2];
	int glyph_index;
	gl_text::color color;
};

class text
{
public:
	friend class renderer;
	struct character {
		float x;
		char c;
		const font *font_;
		const glyph *g;
	};

	text(const font *font, float r, float g, float b, float a, const std::string *str = NULL);
	text(const font *font, float r, float g, float b, float a, const char *str = NULL);
	text();
	~text();

	void set_layout(int width, int height, enum halign halign, enum valign valign);

	void set_background(float r, float g, float b, float a) {
		m_background_color.r = r;
		m_background_color.g = g;
		m_background_color.b = b;
		m_background_color.a = a;
	}

	void pop();

	int get_line_bottom(int i) {
		layout();
		return m_lines[i].bottom;
	}

	int get_line_pos(int i) {
		layout();
		return m_lines[i].y_pos;
	}

	int get_line_top(int i) {
		layout();
		return m_lines[i].top;
	}

	int num_lines() {
		layout();
		return m_lines.size();
	}

	friend text_stream &std::endl(gl_text::text_stream &t);
	void append(const gl_text::glyph &glyph, const color &color);
private:
	std::vector<glyph_instance> m_instance_buffer;
	std::vector<character> m_string;
	int m_layout_width;
	int m_layout_height;
	enum halign m_layout_halign;
	enum valign m_layout_valign;
	color m_background_color;

	struct line {
		int first_char;
		int num_chars;
		int height;
		int width;
		int top;
		int y_pos;
		int bottom;
	};
	std::vector<line> m_lines;

	void layout();
	int m_y_delta; // Offset to apply to y displacment to vertically center text
	bool m_needs_layout; // Set to true if text content or layout information has changed
	bool m_needs_vert_alignment; //Set to true if vertical alignment paramaters have changed i.e. m_y_delta may not be correct
	bool m_buffer_dirty; //Set to true if m_instance_buffer has changed
};
class text;

//
// font desc
//
struct font_desc {
	typeface_t typeface;
	const char *family;
	int style;
	int width;
	int height;
	const char *charset;
};

//
// text stream
//
class text_stream : public std::stringstream
{
	std::vector<const font *> m_font_stack;
	std::vector<color> m_color_stack;
	text &m_out;
public:
	friend text_stream &std::endl(text_stream &t);
	friend text_stream &pop_font(text_stream &t);
	friend text_stream &pop_color(text_stream &t);
	text_stream &operator<<(const font *font);
	text_stream &operator<<(const color &color);

	void flush();

	text_stream(text& out, const font *default_font, const color &default_color);
};

int get_advance(const glyph *prev, const glyph *next);

//
// renderer
//
class renderer
{

	//
	// Freetype state
	//
	FT_Library m_ft_library;
	std::unordered_map<std::string, FT_Face> m_typeface_cache;

	//
	// OpenGL state
	//
	GLuint m_glsl_program;
	GLuint m_fragment_shader;
	GLuint m_vertex_passthrough_shader;
	GLuint m_geometry_shader;
	GLuint m_atlas_texture_name;
	GLuint m_gl_vertex_array;
	GLuint m_stream_vbo;
	GLuint m_texcoord_texture;
	GLuint m_texcoord_texture_buffer;
	GLuint m_glyph_size_texture;
	GLuint m_glyph_size_texture_buffer;
	bool m_use_ARB_buffer_storage;
	bool m_use_ARB_texture_storage;
	bool m_use_ARB_multi_bind;
	bool m_use_ARB_vertex_attrib_binding;
	bool m_use_EXT_direct_state_access;
	int m_sampler_loc;
	int m_ambient_color_loc;
	int m_uvw_sampler_loc;
	int m_glyph_size_sampler_loc;
	int m_mvp_loc;
	color m_ambient_color;
	bool init_program();
	int m_num_chars;
	enum vertex_attrib_locations {
		POS_LOC = 0,
		GLYPH_INDEX_LOC = 1,
		COLOR_LOC = 2,
	};
	void layout_text(glyph_instance *out, const font &font, const color &color,
		const char *text, int num_chars,
		int width, int height,
		enum halign halign, enum valign valign,
		int &y_delta);
	std::vector<uint8_t> m_atlas_buffer;
	std::vector<bool> m_layer_loaded;

	void load_atlas_layer(int i);
	friend class text;
	bool m_initialized;
public:
	renderer();
	~renderer();

	static void grid_fit_mvp_transform(float *mvp_transform, int size_x, int size_y);

	glyph_instance *prepare_render(int num_chars);
	void submit_render(const float *mvp);

	bool render(const font *font, const color &color, const char *text,
		const float *mvp_transform,
		int width, int height,
		enum halign halign, enum valign valign);
	bool render(const font *font, const color &color, const char *text,
		int x, int y,
		int width, int height,
		enum halign halign, enum valign valign);

	bool render(text &txt, int dx, int dy);
	bool render(text &txt, const float *mvp_transform);
	typeface_t get_typeface(const char *path);
	bool initialize(const font_desc *font_descriptions, int count, const font **fonts);
	void set_ambient_color(const color &color);
};

template <typename T>
text_stream &operator<<(text_stream &b, T val) {
	return static_cast<text_stream&>(static_cast<std::stringstream&>(b) << val);
}

inline text_stream &operator<<(text_stream &b, text_stream& (*pf)(text_stream &))
{
	return pf(b);
}

text_stream &pop_font(text_stream &t);
text_stream &pop_color(text_stream &t);


};

#endif
