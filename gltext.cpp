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

#include "gltext.hpp"

#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <math.h>


namespace gl_text {

static const int texture_size = 1024;

static GLuint buffer_bindings[0x10000];

static GLuint get_bound_buffer(GLenum binding_point)
{
	return buffer_bindings[binding_point];
}

static void (*glBindBuffer_org)(GLenum binding_point, GLuint vbo);

static void glBindBuffer_trap(GLenum binding_point, GLuint vbo)
{
	if (buffer_bindings[binding_point] != vbo) {
		glBindBuffer_org(binding_point, vbo);
		buffer_bindings[binding_point] = vbo;
	}
}

static void glNamedBufferDataEXT_emulation(GLuint vbo, GLsizeiptr offset, const void *data, GLenum access)
{
	GLuint prev = get_bound_buffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		offset,
		data,
		access);
	glBindBuffer(GL_ARRAY_BUFFER, prev);
}

static void *glMapNamedBufferRangeEXT_emulation(GLuint vbo, GLintptr offset, GLsizeiptr size, GLbitfield flags)
{
	GLuint prev = get_bound_buffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	void * ret = glMapBufferRange(GL_ARRAY_BUFFER, offset, size, flags);
	glBindBuffer(GL_ARRAY_BUFFER, prev);
	return ret;
}

static GLboolean glUnmapNamedBufferEXT_emulation(GLuint vbo)
{
	GLuint prev = get_bound_buffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLboolean ret = glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, prev);
	return ret;
}

static GLuint bound_program;

static void (*glUseProgram_org)(GLuint program);

static void glUseProgram_trap(GLuint program)
{
	if (bound_program != program) {
		bound_program = program;
		glUseProgram_org(program);
	}
}

void glProgramUniform1iEXT_emulation(GLuint program, GLint uniform, GLint value)
{
	GLuint prev = bound_program;
	glUseProgram(program);
	glUniform1i(uniform, value);
	glUseProgram(prev);
}

//
// text
//

void text::append(const font_const_ptr &font, const color &color, char c)
{
	const glyph *prev_glyph;
	character *prev_character;
	if (m_string.size()) {
		prev_character = &m_string.back();
		prev_glyph = &prev_character->get_glyph();
	} else {
		prev_character = NULL;
		prev_glyph = NULL;
	}
	int i = m_instance_buffer.size();
	m_instance_buffer.resize(m_instance_buffer.size() + 1);
	m_string.resize(m_string.size() + 1);

	const glyph &glyph = font->get_glyph(c);

	int x_pos;
	if (prev_glyph) {
		x_pos = prev_character->x + (prev_glyph->advance_x/64);
	} else {
		x_pos = 0;
	}

	if (prev_glyph && prev_character->font == font) {
		FT_Vector delta;
		if (!FT_Get_Kerning(font->m_typeface,
				prev_glyph->typeface_index,
				glyph.typeface_index,
				FT_KERNING_DEFAULT,
				&delta)) {
			x_pos += ((delta.x + 32)/64);
		}
	}

	glyph_instance &inst = m_instance_buffer[i];
	character &character = m_string[i];
	inst.glyph_index = glyph.atlas_index;
	inst.color = color;
	character.c = c;
	character.x = x_pos;
	character.font = font;
	m_needs_layout = true;
}

text::text(const font_const_ptr &font, GLfloat r, GLfloat g, GLfloat b, GLfloat a, const std::string *str) :
	m_needs_layout(false),
	m_needs_vert_alignment(false),
	m_layout_width(-1),
	m_layout_height(-1),
	m_layout_halign(-1),
	m_layout_valign(-1)
{
	font->select();
	if (str) {
		m_instance_buffer.reserve(str->size());
		m_string.reserve(str->size());
		for (auto c : *str) {
			append(font, color(r, g, b, a), c);
		}
	}
}

text::text(const font_const_ptr &font, GLfloat r, GLfloat g, GLfloat b, GLfloat a, const char *str) :
	m_needs_layout(false),
	m_needs_vert_alignment(false),
	m_layout_width(-1),
	m_layout_height(-1),
	m_layout_halign(-1),
	m_layout_valign(-1)
{
	font->select();
	if (str) {
		while (*str) {
			append(font, color(r, g, b, a), *str);
			str++;
		}
	}
}

text::text() :
	m_needs_layout(false),
	m_needs_vert_alignment(false),
	m_layout_width(-1),
	m_layout_height(-1),
	m_layout_halign(-1),
	m_layout_valign(-1)
{
}

text::~text()
{
}

void text::set_layout(int width, int height, int halign, int valign)
{
	if (m_layout_width != width || m_layout_halign != halign) {
		m_lines.clear();
		m_needs_layout = true;
		m_layout_width = width;
		m_layout_halign = halign;
	}
	if (m_layout_height != height || m_layout_valign != valign) {
		m_needs_vert_alignment = true;
		m_layout_height = height;
		m_layout_valign = valign;
	}
}

void text::pop()
{
	if (!m_string.size())
		return;
	if (m_lines.size()) {
		int last_char = m_string.size() - 1;
		if ((last_char - m_lines.back().first_char) < m_lines.back().num_chars) {
			m_lines.back().num_chars--;
			if (m_lines.back().num_chars == 0) {
				m_lines.pop_back();
			}
		}
	}
	m_string.pop_back();
	m_instance_buffer.pop_back();
	m_needs_layout = true;
}

void text::layout()
{
	if (!m_string.size())
		return;
	if (m_needs_layout) {
		float x_adjust;
		if (!m_lines.size()) {
			m_lines.push_back( {
				.first_char = 0,
				.num_chars = 0,
				.height = 0,
				.width = 0,
				.top = 0,
				.y_pos = 0});
		}
		line *cur = &m_lines.back();
		x_adjust = -((m_string.begin() + cur->first_char)->x);

		int first_line = m_lines.size() - 1;

		//
		//Find line positions first
		//
		auto break_candidate_iter = m_string.end();
		int break_candidate_height;

		cur->num_chars = 0;
		cur->height = 0;
		cur->width = 0;
		cur->top = 0;

		for (auto iter = (m_string.begin() + cur->first_char); iter != m_string.end(); iter++) {
			character *character = &(*iter);
			const glyph &g = character->get_glyph();

			if (m_layout_width > 0 && (character->x + g.left + g.width + x_adjust) > m_layout_width && character->c != ' ') {
				//
				// We've exceeded the line width. If we found a line break candidate earlier
				// move to it's position, otherwise just break the line right here.
				//
				if (break_candidate_iter != m_string.end()) {
					iter = break_candidate_iter;
					cur->height = break_candidate_height;
				}
				character = &(*iter);
				break_candidate_iter = m_string.end();
				cur->num_chars = iter - (m_string.begin() + cur->first_char);
				if (cur->num_chars) {
					m_lines.resize(m_lines.size() + 1);
				}
				cur = &m_lines.back();
				x_adjust = -(*iter).x;
				cur->first_char = iter - m_string.begin();
				cur->num_chars = 0;
				cur->height = 0;
			}
			cur->height = std::max(cur->height, character->font->get_height());
			cur->num_chars++;
			if (character->c == '\n') {
				break_candidate_iter = m_string.end();
				cur->num_chars = iter - (m_string.begin() + cur->first_char) + 1;
				m_lines.resize(m_lines.size() + 1);
				cur = &m_lines.back();
				x_adjust = -(*iter).x;
				cur->first_char = iter - m_string.begin() + 1;
				cur->num_chars = 0;
				cur->height = 0;
			}
			if ((iter + 2) < m_string.end() && (*(iter+1)).c == ' ') {
				break_candidate_iter = iter + 2;
				break_candidate_height = cur->height;
			}
		}
		if (!cur->num_chars) {
			m_lines.pop_back();
		}

		//
		// Compute horizonal alignment and relative vertical line positions
		// TODO: Handle case when text exceeds vertical bounds
		//

		int y_pos = 0;
		if (first_line > 0) {
			y_pos = m_lines[first_line-1].y_pos;
		}
		for (auto iter = m_lines.begin() + first_line; iter != m_lines.end(); iter++) {
			line &line = *iter;
			y_pos += line.height;
			character *first_char = &m_string[line.first_char];
			character *last_char = &m_string[line.first_char + line.num_chars - 1];
			while(last_char->c == ' ' && last_char > first_char) {
				last_char--;
			}
			while(first_char->c == ' ' && last_char > first_char) {
				first_char++;
			}
			int x_adjust;
			int left = first_char->x;
			int right = last_char->x + (last_char->get_glyph().advance_x/64);
			switch(m_layout_halign) {
			case -1:
				x_adjust = 0 - left;
				break;
			case 0:
				x_adjust = (m_layout_width/2) - ((left + right)/2);
				break;
			case 1:
				x_adjust = m_layout_width - right;
				break;
			}
			int top = +INT_MAX;
			int bottom = -INT_MAX;
			for (int i = 0; i < line.num_chars; i++) {
				character &character = m_string[line.first_char + i];
				glyph_instance &g_inst = m_instance_buffer[line.first_char + i];
				const glyph &g = character.get_glyph();
				int char_top = -g.top + y_pos;
				g_inst.pos[0] = character.x + g.left + x_adjust;
				g_inst.pos[1] = char_top;
				top = std::min(top, (int)char_top);
				bottom = std::max(bottom, (int)(char_top + g.height));
			}
			line.top = top;
			line.bottom = bottom;
			line.y_pos = y_pos;
		}
		m_needs_vert_alignment = true;
	}

	if (m_needs_vert_alignment) {
		//
		// Do vertical alignment
		//
		int top = m_lines.front().top;
		int bottom = m_lines.back().bottom;
		switch(m_layout_valign) {
		case -1:
			m_y_delta = 0;
			break;
		case 0:
			m_y_delta = (m_layout_height/2) - ((top + bottom)/2);
			break;
		case 1:
			m_y_delta = m_layout_height - bottom;
			break;
		}
		m_needs_vert_alignment = false;
	}

	return;
}

//
// renderer
//

renderer::renderer(std::string typeface_path) :
	m_typeface_path(typeface_path),
	m_glsl_program(0),
	m_vertex_passthrough_shader(0),
	m_fragment_shader(0),
	m_geometry_shader(0),
	m_use_ARB_buffer_storage(false),
	m_use_ARB_texture_storage(false),
	m_use_ARB_multi_bind(false),
	m_use_ARB_vertex_attrib_binding(false),
	m_use_EXT_direct_state_access(false),
	m_ft_library(NULL),
	m_initialized(false),
	m_atlas_texture_name(0)
{
	FT_Init_FreeType(&m_ft_library);
}

void font::select() const
{
	FT_Set_Pixel_Sizes(m_typeface, m_width, m_height);
}

renderer::~renderer()
{
	if (m_fragment_shader)
		glDeleteShader(m_fragment_shader);
	if (m_geometry_shader)
		glDeleteShader(m_geometry_shader);
	if (m_vertex_passthrough_shader)
		glDeleteShader(m_vertex_passthrough_shader);
	if (m_glsl_program)
		glDeleteProgram(m_glsl_program);
	if (m_ft_library)
		FT_Done_FreeType(m_ft_library);
	if (m_atlas_texture_name)
		glDeleteTextures(1, &m_atlas_texture_name);
}

typeface_t renderer::get_typeface(const std::string &path)
{
	FT_Face face;

	auto iter = m_typeface_cache.find(path);

	if (iter != m_typeface_cache.end()) {
		face = iter->second;
	} else {
		int error = FT_New_Face(m_ft_library, (m_typeface_path + path).c_str(), 0, &face);

		if (error) {
			return NULL;
		}
		m_typeface_cache[path] = face;
	}

	return face;
}

bool renderer::initialize(const std::vector<font_desc> &font_descriptions, std::vector<font_const_ptr> &fonts)
{
	if (m_initialized)
		return false; //You can't reinitialize the renderer

	if (!m_ft_library)
		return false;

	//Query OpenGL extension support
#if GLTEXT_USE_GLEW
	m_use_ARB_buffer_storage = GLEW_ARB_buffer_storage;
	m_use_ARB_texture_storage = GLEW_ARB_texture_storage;
	m_use_ARB_multi_bind = GLEW_ARB_multi_bind;
	m_use_ARB_vertex_attrib_binding = GLEW_ARB_vertex_attrib_binding;
	m_use_EXT_direct_state_access = GLEW_EXT_direct_state_access;
#elif GLTEXT_USE_GLBINDIFY
	m_use_ARB_buffer_storage = gl::ARB_buffer_storage;
	m_use_ARB_texture_storage = gl::ARB_texture_storage;
	m_use_ARB_multi_bind = gl::ARB_multi_bind;
	m_use_ARB_vertex_attrib_binding = gl::ARB_vertex_attrib_binding;
	m_use_EXT_direct_state_access = gl::EXT_direct_state_access;
#endif
	if (!m_use_EXT_direct_state_access) {
		glBindBuffer_org = glBindBuffer;
		glUseProgram_org = glUseProgram;
		glBindBuffer = glBindBuffer_trap;
		glUseProgram = glUseProgram_trap;
		glNamedBufferDataEXT = glNamedBufferDataEXT_emulation;
		glMapNamedBufferRangeEXT = glMapNamedBufferRangeEXT_emulation;
		glUnmapNamedBufferEXT = glUnmapNamedBufferEXT_emulation;
		glProgramUniform1iEXT = glProgramUniform1iEXT_emulation;
#if GLTEXT_USE_GLBINDIFY
		glbindify::gl::BindBuffer = glBindBuffer_trap;
		glbindify::gl::UseProgram = glUseProgram_org;
		glbindify::gl::NamedBufferDataEXT = glNamedBufferDataEXT_emulation;
		glbindify::gl::MapNamedBufferRangeEXT = glMapNamedBufferRangeEXT_emulation;
		glbindify::gl::UnmapNamedBufferEXT = glUnmapNamedBufferEXT_emulation;
		glbindify::gl::ProgramUniform1iEXT = glProgramUniform1iEXT_emulation;
#endif
	}

	//Need at least one font
	if (font_descriptions.empty())
		return false;

	//Create GLSL program
	if (!init_program())
		return false;

	//
	// Rasterize all the glyphs for this atlas and insert them into priority queue
	// primarily sorted by height and secondarily sorted by width.
	//
	class glyph_comp {
	public:
		bool operator()(const glyph *a, const glyph *b) {
			if (a->height < b->height) {
				return true;
			} else if (a->height == b->height && a->width < b->width) {
				return true;
			} else {
				return false;
			}
		}
	};
	std::priority_queue<glyph *, std::vector<glyph *>, glyph_comp> glyph_heap;
	for (auto font_desc : font_descriptions) {
		font *f = new font();
		typeface_t typeface = get_typeface(font_desc.path);
		int width = font_desc.width;
		int height = font_desc.height;

		if (!typeface)
			return false;

		int max_char = 0;
		for (auto c : font_desc.charset)
			if (c > max_char)
				max_char = c;
		f->m_glyphs.resize(max_char + 1);
		f->m_width = width;
		f->m_height = height;
		f->m_typeface = typeface;
		f->m_family = font_desc.family;
		f->m_style = font_desc.style;
		FT_Set_Pixel_Sizes(typeface, width, height);

		for (auto c : font_desc.charset) {
			glyph &g = f->m_glyphs[c];
			int index = FT_Get_Char_Index(typeface, c);
			FT_Load_Glyph(typeface, index, 0/* flags */);
			FT_Render_Glyph(typeface->glyph, FT_RENDER_MODE_NORMAL);
			g.pitch = typeface->glyph->bitmap.pitch;
			g.width = typeface->glyph->bitmap.width;
			g.height = typeface->glyph->bitmap.rows;
			size_t image_size = g.pitch * g.height;
			g.buffer.resize(image_size);
			memcpy(g.buffer.data(), typeface->glyph->bitmap.buffer, image_size);
			g.left = typeface->glyph->bitmap_left;
			g.top = typeface->glyph->bitmap_top;
			g.advance_x = typeface->glyph->advance.x;
			g.advance_y = typeface->glyph->advance.y;
			g.typeface_index = index;
			glyph_heap.push(&g);
		}
		fonts.push_back(font_const_ptr(f));
	}

	//
	// Position the glyphs in the altas's uvw space
	//
	std::vector<glyph *> glyphs;
	glyphs.reserve(glyph_heap.size());
	int u = 0;
	int v = 0;
	int w = 0;
	int height = 0;
	bool first = true;
	while (!glyph_heap.empty()) {
		glyph *g = glyph_heap.top();
		glyphs.push_back(g);
		if (first) {
			first = false;
			height = g->height;
		}
		if ((u + g->width) > texture_size) {
			u = 0;
			v += height;
			if ((v + g->height) > texture_size) {
				u = 0;
				v = 0;
				w++;
			}
			height = g->height;
		}
		g->u = u;
		g->v = v;
		g->w = w;
		glyph_heap.pop();
		u += g->width;
	}
	int tex_array_size = w + 1;

	//
	//Blit the glyph bitmaps into a CPU texture
	//
	std::vector<uint8_t> atlas_buffer(tex_array_size * texture_size * texture_size);
	struct texcoord {
		int16_t u;
		int16_t v;
		int16_t w;
		int16_t padding;
	};

	std::vector<int16_t> texcoord_array;
	std::vector<int16_t> glyph_size_array;
	for (glyph *g : glyphs) {
		uint8_t *dest = atlas_buffer.data() + g->u + (g->v * texture_size) + (g->w * texture_size * texture_size);
		uint8_t *source = g->buffer.data();
		for (int i = 0; i < g->height; i++) {
			memcpy(dest, source, g->width);
			dest += texture_size;
			source += g->pitch;
		}
		g->atlas_index = texcoord_array.size()/4;
		texcoord_array.push_back((int16_t)g->u);
		texcoord_array.push_back((int16_t)g->v);
		texcoord_array.push_back((int16_t)g->w);
		texcoord_array.push_back(0);
		glyph_size_array.push_back((int16_t)g->width);
		glyph_size_array.push_back((int16_t)g->height);
	}

	//Setup texcoord texture buffer
	glGenBuffers(1, &m_texcoord_texture_buffer);
	glBindBuffer(GL_TEXTURE_BUFFER, m_texcoord_texture_buffer);
	glBufferData(GL_TEXTURE_BUFFER, texcoord_array.size() * 2, texcoord_array.data(), GL_STATIC_DRAW);
	glGenTextures(1, &m_texcoord_texture);
	glBindTexture(GL_TEXTURE_BUFFER, m_texcoord_texture);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA16I, m_texcoord_texture_buffer);

	//Setup glyph size texture buffer
	glGenBuffers(1, &m_glyph_size_texture_buffer);
	glBindBuffer(GL_TEXTURE_BUFFER, m_glyph_size_texture_buffer);
	glBufferData(GL_TEXTURE_BUFFER, glyph_size_array.size() * 2, glyph_size_array.data(), GL_STATIC_DRAW);
	glGenTextures(1, &m_glyph_size_texture);
	glBindTexture(GL_TEXTURE_BUFFER, m_glyph_size_texture);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RG16I, m_glyph_size_texture_buffer);

	//
	// Upload the altas texture to the GPU
	//
	glGenTextures(1, &m_atlas_texture_name);
	if (m_use_EXT_direct_state_access) {
		if (m_use_ARB_texture_storage) {
			glTextureStorage3DEXT(m_atlas_texture_name,
				GL_TEXTURE_2D_ARRAY,
				1, /* layers */
				GL_R8,
				texture_size, texture_size, tex_array_size /* uvw size */);
			glTextureSubImage3DEXT(m_atlas_texture_name,
				GL_TEXTURE_2D_ARRAY,
				0, /* layer */
				0, 0, 0, /* uvw offset */
				texture_size, texture_size, tex_array_size, /* uvw size */
				GL_RED, GL_UNSIGNED_BYTE, atlas_buffer.data());
		} else {
			glTextureImage3DEXT(m_atlas_texture_name,
				GL_TEXTURE_2D_ARRAY,
				0, /* layers */
				GL_R8,
				texture_size, texture_size, tex_array_size /* uvw size */,
				0, /* border */
				GL_RED,
				GL_UNSIGNED_BYTE,
				atlas_buffer.data());
		}
		glTextureParameteriEXT(m_atlas_texture_name, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteriEXT(m_atlas_texture_name, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteriEXT(m_atlas_texture_name, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteriEXT(m_atlas_texture_name, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	} else {
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_atlas_texture_name);
		if (m_use_ARB_texture_storage) {
			glTexStorage3D(
				GL_TEXTURE_2D_ARRAY,
				1, /* layers */
				GL_R8,
				texture_size, texture_size, tex_array_size /* uvw size */);
			glTexSubImage3D(
				GL_TEXTURE_2D_ARRAY,
				0, /* layer */
				0, 0, 0, /* uvw offset */
				texture_size, texture_size, tex_array_size, /* uvw size */
				GL_RED, GL_UNSIGNED_BYTE, atlas_buffer.data());
		} else {
			glTexImage3D(
				GL_TEXTURE_2D_ARRAY,
				0, /* layers */
				GL_R8,
				texture_size, texture_size, tex_array_size /* uvw size */,
				0, /* border */
				GL_RED,
				GL_UNSIGNED_BYTE,
				atlas_buffer.data());
		}
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	m_initialized = true;
	return m_initialized;
}

bool renderer::init_program()
{
	const char *vertex_passthrough_shader_text =
		"#version 330\n"
		"layout (location = 0) in vec2 pos_v;\n"
		"layout (location = 1) in int glyph_index_v;\n"
		"layout (location = 2) in vec4 color_v;\n"
		"out vec2 pos;\n"
		"out int glyph_index;\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
				"pos = pos_v;\n"
				"color = color_v;\n"
				"glyph_index = glyph_index_v;\n"
				"gl_Position = vec4(0, 0, 1, 1);\n"
		"}\n";

	const char *geometry_shader_text =
		"#version 330\n"
		"layout(points) in;\n"
		"layout(triangle_strip, max_vertices=4) out;\n"
		"in vec2 pos[1];\n"
		"in vec4 color[1];\n"
		"in int glyph_index[1];\n"
		"uniform vec2 scale;\n"
		"uniform vec2 disp;\n"
		"uniform usamplerBuffer glyph_size_sampler;\n"
		"uniform usamplerBuffer uvw_sampler;\n"
		"\n"
		"out vec3 texcoord_f;\n"
		"out vec4 color_f;\n"
		"\n"
		"void genVertex(vec2 corner, vec2 size, vec3 texcoord)\n"
		"{\n"
			"gl_Position = vec4((pos[0] + disp + (corner * size)) * scale + vec2(-1, 1), 1, 1);\n"
			"texcoord_f = texcoord + vec3(corner * size, 0);\n"
			"color_f = color[0];\n"
			"EmitVertex();\n"
		"}\n"
		"\n"
		"void main()\n"
		"{\n"
			"if (glyph_index[0] >= 0) {\n"
				"vec2 size = vec2(texelFetch(glyph_size_sampler, glyph_index[0]).rg);\n"
				"vec3 texcoord = vec3(texelFetch(uvw_sampler, glyph_index[0]).rgb);\n"
				"genVertex(vec2(0,0), size, texcoord);\n"
				"genVertex(vec2(1,0), size ,texcoord);\n"
				"genVertex(vec2(0,1), size, texcoord);\n"
				"genVertex(vec2(1,1), size, texcoord);\n"
				"EndPrimitive();\n"
			"}\n"
		"}\n";

	const char *fragment_shader_text =
		"#version 330\n"
		"uniform sampler2DArray sampler;\n"
		"in vec3 texcoord_f;\n"
		"in vec4 color_f;\n"
		"out vec4 frag_color;\n"
		"void main()\n"
		"{\n"
			"frag_color = color_f * vec4(texelFetch(sampler, ivec3(texcoord_f), 0).r);\n"
		"}\n";

	//std::cout << m_use_ARB_buffer_storage << ":" << m_use_ARB_multi_bind << ":" << m_use_ARB_vertex_attrib_binding << ":" << m_use_EXT_direct_state_access << std::endl;

	GLint success;
	glGenVertexArrays(1, &m_gl_vertex_array);
	glBindVertexArray(m_gl_vertex_array);

	m_geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(m_geometry_shader, 1, (const char **)&geometry_shader_text, NULL);
	glCompileShader(m_geometry_shader);
	glGetShaderiv(m_geometry_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char info_log[1000];
		glGetShaderInfoLog(m_geometry_shader, sizeof(info_log), NULL, info_log);
		std::cout << "renderer: Geometry shader compile failed" << std::endl
			<< info_log << std::endl;
		glDeleteShader(m_geometry_shader);
		m_geometry_shader = 0;
		return false;
	}

	m_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragment_shader, 1, (const char **)&fragment_shader_text, NULL);
	glCompileShader(m_fragment_shader);
	glGetShaderiv(m_fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char info_log[1000];
		glGetShaderInfoLog(m_fragment_shader, sizeof(info_log), NULL, info_log);
		std::cout << "renderer: Fragment shader compile failed" << std::endl
			<< info_log << std::endl;
		glDeleteShader(m_fragment_shader);
		m_fragment_shader = 0;
		glDeleteShader(m_geometry_shader);
		m_geometry_shader = 0;
		return false;
	}

	m_vertex_passthrough_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertex_passthrough_shader, 1, (const char **)&vertex_passthrough_shader_text, NULL);
	glCompileShader(m_vertex_passthrough_shader);
	glGetShaderiv(m_vertex_passthrough_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char info_log[1000];
		glGetShaderInfoLog(m_vertex_passthrough_shader, sizeof(info_log), NULL, info_log);
		std::cout << "renderer: Vertex point shader compile failed" << std::endl
			<< info_log << std::endl;
		glDeleteShader(m_fragment_shader);
		m_fragment_shader = 0;
		glDeleteShader(m_vertex_passthrough_shader);
		m_vertex_passthrough_shader = 0;
		glDeleteShader(m_geometry_shader);
		m_geometry_shader = 0;
		return false;
	}

	m_glsl_program = glCreateProgram();
	glAttachShader(m_glsl_program, m_vertex_passthrough_shader);
	glAttachShader(m_glsl_program, m_geometry_shader);
	glAttachShader(m_glsl_program, m_fragment_shader);
	glLinkProgram(m_glsl_program);
	glGetProgramiv(m_glsl_program, GL_LINK_STATUS, &success);
	if (!success) {
		char info_log[1000];
		glGetProgramInfoLog(m_glsl_program, sizeof(info_log), NULL, info_log);
		std::cout << "renderer: Program link failed" << std::endl
			<< info_log << std::endl;
		glDeleteShader(m_fragment_shader);
		m_fragment_shader = 0;
		glDeleteShader(m_vertex_passthrough_shader);
		m_vertex_passthrough_shader = 0;
		glDeleteProgram(m_glsl_program);
		m_glsl_program = 0;
		return false;
	}

	//
	// Common setup for GL 3.x and GL 4.x
	//
	glEnableVertexAttribArray(GLYPH_INDEX_LOC);
	glEnableVertexAttribArray(POS_LOC);
	glEnableVertexAttribArray(COLOR_LOC);

	if (m_use_ARB_vertex_attrib_binding) {
		//
		// Glyph instance array setup
		//
		glVertexAttribFormat(POS_LOC,
			2,
			GL_FLOAT,
			GL_FALSE,
			offsetof(text::glyph_instance, pos));
		glVertexAttribBinding(POS_LOC, 1);

		glVertexAttribFormat(COLOR_LOC,
			4,
			GL_FLOAT,
			GL_FALSE,
			offsetof(text::glyph_instance, color));
		glVertexAttribBinding(COLOR_LOC, 1);

		glVertexAttribIFormat(GLYPH_INDEX_LOC,
			1,
			GL_UNSIGNED_INT,
			offsetof(text::glyph_instance, glyph_index));
		glVertexAttribBinding(GLYPH_INDEX_LOC, 1);
	}

	glGenBuffers(1, &m_stream_vbo);
	if (m_use_ARB_vertex_attrib_binding) {
		glBindVertexBuffer(1, /*binding point */
			m_stream_vbo,
			0, /* offset */
			sizeof(text::glyph_instance) /* stride */);
	} else {
		glBindBuffer(GL_ARRAY_BUFFER, m_stream_vbo);

		glVertexAttribPointer(POS_LOC,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(text::glyph_instance),
			(void *)offsetof(text::glyph_instance, pos));

		glVertexAttribPointer(COLOR_LOC,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(text::glyph_instance),
			(void *)offsetof(text::glyph_instance, color));

		glVertexAttribIPointer(GLYPH_INDEX_LOC,
			1,
			GL_UNSIGNED_INT,
			sizeof(text::glyph_instance),
			(void *)offsetof(text::glyph_instance, glyph_index));
	}

	//Cache uniform locations
	m_scale_loc = glGetUniformLocation(m_glsl_program, "scale");
	m_disp_loc = glGetUniformLocation(m_glsl_program, "disp");
	m_sampler_loc = glGetUniformLocation(m_glsl_program, "sampler");
	m_uvw_sampler_loc = glGetUniformLocation(m_glsl_program, "uvw_sampler");
	m_glyph_size_sampler_loc = glGetUniformLocation(m_glsl_program, "glyph_size_sampler");
	glProgramUniform1iEXT(m_glsl_program, m_sampler_loc, 0);
	glProgramUniform1iEXT(m_glsl_program, m_uvw_sampler_loc, 1);
	glProgramUniform1iEXT(m_glsl_program, m_glyph_size_sampler_loc, 2);
	return true;
}

bool renderer::render(font_const_ptr font, const color &color, const char *text, int x, int y, int width, int height, int halign, int valign)
{
	if (!m_initialized)
		return false;

	size_t num_chars = strlen(text);

	glUseProgram(m_glsl_program);
	glBindVertexArray(m_gl_vertex_array);
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float size_x = viewport[2];
	float size_y = viewport[3];
	glUniform2f(m_scale_loc, 2.0/size_x, -2.0/size_y);
	if (m_use_ARB_multi_bind) {
		GLuint textures[] = {m_atlas_texture_name, m_texcoord_texture, m_glyph_size_texture};
		glBindTextures(0 /* tex unit */, 3, textures);
	} else {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_atlas_texture_name);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_BUFFER, m_texcoord_texture);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_BUFFER, m_glyph_size_texture);
	}

	//Orphan previous buffer
	int buffer_size = sizeof(text::glyph_instance) * num_chars;
	glNamedBufferDataEXT(m_stream_vbo,
			buffer_size,
			NULL,
			GL_STREAM_DRAW);
	//Copy in new data
	m_stream_vbo_data = (text::glyph_instance *) glMapNamedBufferRangeEXT(
		m_stream_vbo,
		0, buffer_size,
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
	if (m_stream_vbo_data == NULL) {
		return false;
	}

	int prev_glyph_index = -1;
	font->select();

	int x_pos = 0;
	int y_pos = font->get_height();
	int i = 0;
	int break_pos = -1;
	int break_line_width = 0;
	int line_start = 0;


	int line_top = y_pos;
	int line_bottom = y_pos;
	int break_line_top = -1;
	int break_line_bottom = -1;
	int top = line_top;
	int bottom = line_bottom;
	while(text[i]) {
		const glyph &g = font->get_glyph(text[i]);
		if (text[i] == ' ') {
			break_pos = i;
			break_line_width = x_pos;
			break_line_top = line_top;
			break_line_bottom = line_bottom;
		}
		int x_pos_prev = x_pos;
		if ((x_pos + g.left + g.width > width && width > 0 && x_pos > 0) || text[i] == '\n') {
			int line_width;
			int line_end;
			if (break_pos != -1 && text[i] != '\n') {
				line_width = break_line_width;
				line_end = break_pos + 1;
				line_top = break_line_top;
				line_bottom = break_line_bottom;
			} else if (text[i] == '\n') {
				line_end = i + 1;
				line_width = x_pos;
			} else {
				line_end = i;
				line_width = x_pos;
			}
			if (width > 0 && (halign == 0 || halign == 1)) {
				int adjust = (width - line_width);
				if (halign == 0) {
					adjust /= 2;
				}
				for (int j = line_start; j < num_chars; j++) {
					m_stream_vbo_data[j].pos[0] += adjust;
				}
			}
			line_start = line_end;
			i = line_start;
			x_pos = 0;
			y_pos += font->get_height();
			break_pos = -1;
			top = std::min(top, line_top);
			bottom = std::max(bottom, line_bottom);
			line_top = y_pos;
			line_bottom = y_pos;
			continue;
		}
		m_stream_vbo_data[i].glyph_index = g.atlas_index;
		m_stream_vbo_data[i].color = color;
		m_stream_vbo_data[i].pos[0] = x_pos + g.left;
		m_stream_vbo_data[i].pos[1] = y_pos - g.top;
		line_top = std::min(line_top, (int)(y_pos - g.top));
		line_bottom = std::max(line_bottom, (int)(y_pos - g.top + g.height));
		x_pos += g.advance_x/64;
		i++;
	}
	if (line_start != num_chars) {
		top = std::min(top, line_top);
		bottom = std::max(bottom, line_bottom);
	}
	if (width > 0 && (halign == 0 || halign == 1)) {
		int adjust = (width - x_pos);
		if (halign == 0) {
			adjust /= 2;
		}
		for (int j = line_start; j < num_chars; j++) {
			m_stream_vbo_data[j].pos[0] += adjust;
		}
	}
	int y_delta;
	if (height > 0 && valign == 0)
		y_delta = (height/2) - ((top + bottom)/2);
	else if (height > 0 && valign == 1)
		y_delta = height - bottom;
	else
		y_delta = 0;
	glUnmapNamedBufferEXT(m_stream_vbo);
	glUniform2f(m_disp_loc, x, y + y_delta);
	glDrawArrays(GL_POINTS, 0, num_chars);
}

//
// Render text 'txt' at position (dx, dy) wrapping text to fit in clip rect
//	 (clip_x, clip_y) -> (clip_x + clip_w, clip_y + clip_h).
//
bool renderer::render(text &txt, int dx, int dy)
{
	if (!m_initialized)
		return false;

	txt.layout();

	size_t num_chars = txt.m_instance_buffer.size();

	glUseProgram(m_glsl_program);
	glBindVertexArray(m_gl_vertex_array);
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float size_x = viewport[2];
	float size_y = viewport[3];
	glUniform2f(m_scale_loc, 2.0/size_x, -2.0/size_y);
	if (m_use_ARB_multi_bind) {
		GLuint textures[] = {m_atlas_texture_name, m_texcoord_texture, m_glyph_size_texture};
		glBindTextures(0 /* tex unit */, 3, textures);
	} else {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_atlas_texture_name);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_BUFFER, m_texcoord_texture);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_BUFFER, m_glyph_size_texture);
	}

	//Orphan previous buffer
	int buffer_size = sizeof(text::glyph_instance) * txt.m_instance_buffer.size();
	glNamedBufferDataEXT(m_stream_vbo,
			buffer_size,
			NULL,
			GL_STREAM_DRAW);
	//Copy in new data
	m_stream_vbo_data = (text::glyph_instance *) glMapNamedBufferRangeEXT(
		m_stream_vbo,
		0, buffer_size,
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
	if (m_stream_vbo_data != NULL) {
		memcpy(m_stream_vbo_data, txt.m_instance_buffer.data(), buffer_size);
		glUnmapNamedBufferEXT(m_stream_vbo);
	}
	glUniform2f(m_disp_loc, dx, dy + txt.m_y_delta);
	glDrawArrays(GL_POINTS, 0, num_chars);
}

text_stream &text_stream::operator<<(font_const_ptr font)
{
	flush();
	m_font_stack.push_back(font);
	return *this;
}

text_stream &text_stream::operator<<(const color &color)
{
	flush();
	m_color_stack.push_back(color);
	return *this;
}

text_stream &pop_font(text_stream &t)
{
	t.flush();
	if (t.m_font_stack.size() > 1) {
		t.m_font_stack.pop_back();
	}
	return t;
}

text_stream &pop_color(text_stream &t)
{
	t.flush();
	if (t.m_color_stack.size() > 1)
		t.m_color_stack.pop_back();
	return t;
}

void text_stream::flush()
{
	int c;
	m_font_stack.back()->select();
	while ((c = std::stringstream::get()) != EOF) {
		m_out.append(m_font_stack.back(), m_color_stack.back(), c);
	}
	clear();
}

text_stream::text_stream(text &out, font_const_ptr &default_font, color default_color)
	: m_out(out)
{
	m_font_stack.push_back(default_font);
	m_color_stack.push_back(default_color);
}

}

namespace std {

gl_text::text_stream &endl(gl_text::text_stream &t)
{
	t.flush();
	t.m_out.append(t.m_font_stack.back(), t.m_color_stack.back(), '\n');
	return t;
}

};
