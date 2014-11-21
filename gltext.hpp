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
	class text_builder;
};

namespace std {
	gl_text::text_builder &endl(gl_text::text_builder &t);
};

namespace gl_text {

struct gl_bounding_box {
	GLfloat upper_left[2];
	GLfloat lower_right[2];
};

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
	friend class renderer;
	friend class text;

	font() { }

	const glyph &get_glyph(char c) const {
		return m_glyphs[c];
	}
public:
	void select() const;
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

class text_builder;

class text
{
public:
	friend class renderer;
	friend class text_builder;

	struct glyph_instance {
		gl_bounding_box v_bounds; /* Position of glyph within the text */
		GLint uvw[4]; /* position of glyph in texture*/
		gl_text::color color; /* RGBA color */
	};

	text(const font_const_ptr &font, GLfloat r, GLfloat g, GLfloat b, GLfloat a, const std::string &str);
	~text();

	int get_x_cursor() {
		return m_x_cursor;
	}
	int get_y_min() {
		return m_y_min;
	}
	int get_y_max() {
		return m_y_max;
	}
	int get_width() {
		return m_width;
	}
	int get_height() {
		return m_y_max - m_y_min;
	}
	friend text_builder &std::endl(gl_text::text_builder &t);
private:
	std::vector<glyph_instance> m_instance_buffer;
	std::vector<int> m_line_breaks;
	void append(const font_const_ptr &font, const color &color, char c, int &index);
	int m_x_cursor;
	int m_y_min;
	int m_y_max;
	int m_width;
	GLuint m_gl_buffer;
};
class text;
typedef std::shared_ptr<text> text_ptr;

class text_builder : public std::stringstream {
	text *m_text;
	std::vector<font_const_ptr> m_font_stack;
	std::vector<color> m_color_stack;
	void gen_glyphs();
	int m_prev_index;
public:
	text_builder(const font_const_ptr &font, color color);
	text *get_text();

	friend text_builder &std::endl(text_builder &t);
	friend text_builder &pop_font(text_builder &t);
	friend text_builder &pop_color(text_builder &t);
	text_builder &operator<<(font_const_ptr font);
	text_builder &operator<<(const color &color);
};

template <typename T>
text_builder &operator<<(text_builder &b, T val) {
	return static_cast<text_builder&>(static_cast<std::stringstream&>(b) << val);
}

inline text_builder &operator<<(text_builder &b, text_builder& (*pf)(text_builder &))
{
	return pf(b);
}

text_builder &pop_font(text_builder &t);
text_builder &pop_color(text_builder &t);

//
// font desc
//
struct font_desc {
	typeface_t typeface;
	int width;
	int height;
	std::string charset;
};

//
// renderer
//
class renderer
{
	FT_Library m_ft_library;
	std::unordered_map<std::string, FT_Face> m_typeface_cache;
	GLuint m_glsl_program;

	GLuint m_vertex_shader;
	GLuint m_fragment_shader;

	GLuint m_vertex_passthrough_shader;
	GLuint m_geometry_shader;
	GLuint m_atlas_texture_name;

	std::string m_typeface_path;

	bool m_use_ARB_buffer_storage;
	bool m_use_ARB_texture_storage;
	bool m_use_ARB_multi_bind;
	bool m_use_ARB_vertex_attrib_binding;
	bool m_use_EXT_direct_state_access;

	bool init_program();
	GLuint m_gl_vertex_array;

	enum vertex_attrib_locations {
		VBOX_LOC = 0,
		UVW_LOC = 1,
		COLOR_LOC = 2,
	};

	int m_scale_loc;
	int m_disp_loc;
	int m_sampler_loc;
	bool m_initialized;
public:
	renderer(std::string typeface_path = "");
	~renderer();
	bool render(text &txt, int dx, int dy);
	typeface_t get_typeface(const std::string &path);
	bool initialize(const std::vector<font_desc> &font_descriptions, std::vector<font_const_ptr> &fonts);
};


};

#endif
