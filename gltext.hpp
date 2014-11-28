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
#include <memory>
#include <sstream>

#include <ft2build.h>
#include FT_FREETYPE_H
typedef FT_Face typeface_t;

namespace gl_text {
	class text_stream;
};

namespace std {
	gl_text::text_stream &endl(gl_text::text_stream &t);
};

namespace gl_text {

struct bounding_box {
	float upper_left[2];
	float size[2];
};

class font;

//
// glyph
//
struct glyph {
	/* index into typeface */
	int index;

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

	/* Glyph bitmap */
	int width;
	int height;
	int pitch;

	glyph() : index(-1), left(0), top(0), advance_x(0), advance_y(0), u(0), v(0), w(0), width(0), height(0), pitch(0) {}

	std::vector<uint8_t> buffer;
};

class renderer;
typedef std::shared_ptr<renderer> renderer_ptr;

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
	friend class renderer;
	friend class text;
	friend class text_stream;

	font() {
		m_glyphs.resize(256);
	}

	int width() const {
		return m_width;
	}

	int height() const {
		return m_height;
	}

	const std::string &family() const {
		return m_family;
	}

	int style() const {
		return m_style;
	}
	const glyph &get_glyph(char c) const {
		return m_glyphs[c];
	}

public:
	void select() const;
	int get_height() const {
		return m_height;
	}
	int get_width() const {
		return m_width;
	}
	~font() { }
};
typedef std::shared_ptr<const font> font_const_ptr;

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

class text
{
public:
	friend class renderer;

	struct character {
		float x;
		char c;
		font_const_ptr font;
		const glyph &get_glyph() const {
			return font->get_glyph(c);
		}
	};

	struct glyph_instance {
		bounding_box v_bounds; /* Position of glyph within the text */
		GLint uvw[4]; /* position of glyph in texture*/
		gl_text::color color; /* RGBA color */
	};

	text(const font_const_ptr &font, GLfloat r, GLfloat g, GLfloat b, GLfloat a, const std::string *str = NULL);
	text();
	~text();

	typedef std::vector<character>::iterator iterator;

	iterator begin() {
		return m_string.begin();
	};

	iterator end() {
		return m_string.end();
	};

	void set_layout(int width, int height, int halign, int valign);

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
	void append(const font_const_ptr &font, const color &color, char c);
private:
	std::vector<glyph_instance> m_instance_buffer;
	std::vector<character> m_string;
	int m_layout_width;
	int m_layout_height;
	int m_layout_halign;
	int m_layout_valign;

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
	int m_y_delta;
	GLuint m_gl_buffer;
	bool m_needs_layout;
	bool m_needs_vert_alignment;
	bool m_buffer_dirty;
};
class text;
typedef std::shared_ptr<text> text_ptr;

enum font_style {
	STYLE_REGULAR = 0,
	STYLE_ITALIC = 1,
	STYLE_BOLD = 2,
};

//
// font desc
//
struct font_desc {
	std::string path;
	std::string family;
	int style;
	int width;
	int height;
	std::string charset;
};

//
// text stream
//
class text_stream : public std::stringstream
{
	std::vector<font_const_ptr> m_font_stack;
	std::vector<color> m_color_stack;
	text &m_out;
public:
	friend text_stream &std::endl(text_stream &t);
	friend text_stream &pop_font(text_stream &t);
	friend text_stream &pop_color(text_stream &t);
	text_stream &operator<<(font_const_ptr font);
	text_stream &operator<<(const color &color);

	void flush();

	text_stream(text& out, font_const_ptr &default_font, color default_color);
};

//
// renderer
//
class renderer
{

	//
	// Freetype state
	//
	std::string m_typeface_path;
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
	bool m_use_ARB_buffer_storage;
	bool m_use_ARB_texture_storage;
	bool m_use_ARB_multi_bind;
	bool m_use_ARB_vertex_attrib_binding;
	bool m_use_EXT_direct_state_access;
	int m_scale_loc;
	int m_disp_loc;
	int m_sampler_loc;

	bool init_program();

	enum vertex_attrib_locations {
		VBOX_LOC = 0,
		UVW_LOC = 1,
		COLOR_LOC = 2,
	};

	bool m_initialized;
public:
	renderer(std::string typeface_path = "");
	~renderer();
	bool render(text &txt, int dx, int dy);
	typeface_t get_typeface(const std::string &path);
	bool initialize(const std::vector<font_desc> &font_descriptions, std::vector<font_const_ptr> &fonts);
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
