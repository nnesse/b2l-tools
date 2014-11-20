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

//
// text
//


void text::append(const font_const_ptr &font, const color &color, char c, int &prev_index)
{
	int i = m_instance_buffer.size();
	m_instance_buffer.resize(m_instance_buffer.size() + 1);
	const glyph &glyph = font->get_glyph(c);

	if (prev_index >= 0) {
		FT_Vector delta;
		if (!FT_Get_Kerning(font->m_typeface,
				prev_index,
				glyph.index,
				FT_KERNING_DEFAULT,
				&delta)) {
			m_x_cursor += delta.x/64.0;
		}
	}
	prev_index = glyph.index;

	glyph_instance &inst = m_instance_buffer[i];
	inst.uvw[0] = glyph.u;
	inst.uvw[1] = glyph.v;
	inst.uvw[2] = glyph.w;
	inst.v_bounds.upper_left[0] = m_x_cursor + glyph.left;
	inst.v_bounds.upper_left[1] = -glyph.top;
	inst.v_bounds.lower_right[0] = glyph.width;
	inst.v_bounds.lower_right[1] = glyph.height;
	inst.color = color;
	m_x_cursor += glyph.advance_x / 64.0;
	m_width = inst.v_bounds.lower_right[0];
	m_y_min = std::min(-glyph.top, m_y_min);
	m_y_max = std::max(-glyph.top + glyph.height, m_y_max);
}

text::text(const font_const_ptr &font, GLfloat r, GLfloat g, GLfloat b, GLfloat a, const std::string &str) :
	m_atlas(font->get_atlas()), m_gl_buffer(0)
{
	m_instance_buffer.reserve(str.size());

	m_x_cursor = 0;
	m_y_min = 0;
	m_y_max = 0;
	m_width = 0;

	font->select();
	int prev_index = -1;
	for (int i = 0; i < str.size(); i++) {
		append(font, color(r, g, b, a), (int)str[i], prev_index);
	}
}

text::~text()
{
	if (m_gl_buffer)
		glDeleteBuffers(1, &m_gl_buffer);
}

//
// renderer
//

renderer::renderer(std::string typeface_path) :
	m_typeface_path(typeface_path),
	m_glsl_program(0),
	m_vertex_shader(0),
	m_fragment_shader(0),
	m_geometry_shader(0)
{
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
	FT_Init_FreeType(&m_ft_library);
}

font::atlas::~atlas() {
	glDeleteTextures(1, &m_id);
}

void font::select() const
{
	FT_Set_Pixel_Sizes(m_typeface, m_width, m_height);
}

renderer::~renderer()
{
	if (m_fragment_shader)
		glDeleteShader(m_fragment_shader);
	if (m_vertex_shader)
		glDeleteShader(m_vertex_shader);
	if (m_geometry_shader)
		glDeleteShader(m_vertex_shader);
	if (m_glsl_program)
		glDeleteProgram(m_glsl_program);
	FT_Done_FreeType(m_ft_library);
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

bool renderer::generate_fonts(const std::vector<font_desc> &font_descriptions, std::vector<font_const_ptr> &fonts)
{
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
		typeface_t typeface = font_desc.typeface;
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
			g.index = index;
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
	for (glyph *g : glyphs) {
		uint8_t *dest = atlas_buffer.data() + g->u + (g->v * texture_size) + (g->w * texture_size * texture_size);
		uint8_t *source = g->buffer.data();
		for (int i = 0; i < g->height; i++) {
			memcpy(dest, source, g->width);
			dest += texture_size;
			source += g->pitch;
		}
	}

	GLuint m_tex;
	//
	// Upload the altas texture to the GPU
	//
	glGenTextures(1, &m_tex);
	if (m_use_EXT_direct_state_access) {
		if (m_use_ARB_texture_storage) {
			glTextureStorage3DEXT(m_tex,
				GL_TEXTURE_2D_ARRAY,
				1, /* layers */
				GL_R8,
				texture_size, texture_size, tex_array_size /* uvw size */);
			glTextureSubImage3DEXT(m_tex,
				GL_TEXTURE_2D_ARRAY,
				0, /* layer */
				0, 0, 0, /* uvw offset */
				texture_size, texture_size, tex_array_size, /* uvw size */
				GL_RED, GL_UNSIGNED_BYTE, atlas_buffer.data());
		} else {
			glTextureImage3DEXT(m_tex,
				GL_TEXTURE_2D_ARRAY,
				0, /* layers */
				GL_R8,
				texture_size, texture_size, tex_array_size /* uvw size */,
				0, /* border */
				GL_RED,
				GL_UNSIGNED_BYTE,
				atlas_buffer.data());
		}
		glTextureParameteriEXT(m_tex, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteriEXT(m_tex, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteriEXT(m_tex, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteriEXT(m_tex, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	} else {
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_tex);
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

	font::atlas_ptr atlas(new font::atlas(m_tex));

	//
	// Associate the generated texture with the fonts
	//
	for (auto f: fonts) {
		(const_cast<font&>(*f)).m_atlas = atlas;
	}
	return true;
}

bool renderer::init_program()
{
	const char *vertex_passthrough_shader_text =
		"#version 330\n"
		"layout (location = 0) in vec4 vbox_v;\n"
		"layout (location = 1) in uvec3 uvw_v;\n"
		"layout (location = 2) in vec4 color_v;\n"
		"out vec4 vbox;\n"
		"out uvec3 uvw;\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
				"vbox = vbox_v;\n"
				"uvw = uvw_v;\n"
				"color = color_v;\n"
				"gl_Position = vec4(0, 0, 1, 1);\n"
		"}\n";

	const char *geometry_shader_text =
		"#version 330\n"
		"layout(points) in;\n"
		"layout(triangle_strip, max_vertices=4) out;\n"
		"in vec4 vbox[1];\n"
		"in uvec3 uvw[1];\n"
		"in vec4 color[1];\n"
		"uniform vec2 scale;\n"
		"uniform vec2 disp;\n"
		"\n"
		"out vec3 texcoord_f;\n"
		"out vec4 color_f;\n"
		"\n"
		"uniform usampler1D uvw_sampler;\n"
		"uniform usampler1D uvsize_sampler;\n"
		"\n"
		"void genVertex(vec2 corner)\n"
		"{\n"
			"gl_Position = vec4((vbox[0].xy + disp + (corner * vbox[0].zw)) * scale + vec2(-1, 1), 1, 1);\n"
			"texcoord_f = vec3(uvw[0]) + vec3(corner * vbox[0].zw, 0);\n"
			"color_f = color[0];\n"
			"EmitVertex();\n"
		"}\n"
		"\n"
		"void main()\n"
		"{\n"
			"genVertex(vec2(0,0));\n"
			"genVertex(vec2(1,0));\n"
			"genVertex(vec2(0,1));\n"
			"genVertex(vec2(1,1));\n"
			"EndPrimitive();\n"
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
	glEnableVertexAttribArray(UVW_LOC);
	glEnableVertexAttribArray(VBOX_LOC);
	glEnableVertexAttribArray(COLOR_LOC);

	if (m_use_ARB_vertex_attrib_binding) {
		//
		// Glyph instance array setup
		//
		glVertexAttribFormat(VBOX_LOC,
			4,
			GL_FLOAT,
			GL_FALSE,
			offsetof(text::glyph_instance, v_bounds));
		glVertexAttribBinding(VBOX_LOC, 1);

		glVertexAttribFormat(COLOR_LOC,
			4,
			GL_FLOAT,
			GL_FALSE,
			offsetof(text::glyph_instance, color));
		glVertexAttribBinding(COLOR_LOC, 1);

		glVertexAttribIFormat(UVW_LOC,
			3,
			GL_UNSIGNED_INT,
			offsetof(text::glyph_instance, uvw));
		glVertexAttribBinding(UVW_LOC, 1);
	}

	//Cache uniform locations
	m_scale_loc = glGetUniformLocation(m_glsl_program, "scale");
	m_disp_loc = glGetUniformLocation(m_glsl_program, "disp");
	m_sampler_loc = glGetUniformLocation(m_glsl_program, "sampler");
	if (m_use_EXT_direct_state_access) {
		glProgramUniform1iEXT(m_glsl_program, m_sampler_loc, 0);
	} else {
		glUseProgram(m_glsl_program);
		glUniform1i(m_sampler_loc, 0);
	}
	return true;
}

//
// Render text 'txt' at position (dx, dy) wrapping text to fit in clip rect
//	 (clip_x, clip_y) -> (clip_x + clip_w, clip_y + clip_h).
//
bool renderer::render(text &txt, int dx, int dy)
{
	size_t num_chars = txt.m_instance_buffer.size();
	if (!m_glsl_program) {
		if (!init_program())
			return false;
	}

	glUseProgram(m_glsl_program);
	glBindVertexArray(m_gl_vertex_array);
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float size_x = viewport[2];
	float size_y = viewport[3];
	glUniform2f(m_scale_loc, 2.0/size_x, -2.0/size_y);
	GLuint tex_name = txt.m_atlas->get_name();
	if (m_use_ARB_multi_bind) {
		glBindTextures(0 /* tex unit */, 1, &tex_name);
	} else {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D_ARRAY, tex_name);
	}

	if(!txt.m_gl_buffer) {
		glGenBuffers(1, &txt.m_gl_buffer);
		if (m_use_EXT_direct_state_access) {
			if (m_use_ARB_buffer_storage) {
				glNamedBufferStorageEXT(txt.m_gl_buffer,
						sizeof(text::glyph_instance) * txt.m_instance_buffer.size(),
						txt.m_instance_buffer.data(),
						0);
			} else {
				glNamedBufferDataEXT(txt.m_gl_buffer,
						sizeof(text::glyph_instance) * txt.m_instance_buffer.size(),
						txt.m_instance_buffer.data(),
						0);
			}
		} else {
			glBindBuffer(GL_ARRAY_BUFFER, txt.m_gl_buffer);
			if (m_use_ARB_buffer_storage) {
				glBufferStorage(GL_ARRAY_BUFFER,
						sizeof(text::glyph_instance) * txt.m_instance_buffer.size(),
						txt.m_instance_buffer.data(),
						0);
			} else {
				glBufferData(GL_ARRAY_BUFFER,
						sizeof(text::glyph_instance) * txt.m_instance_buffer.size(),
						txt.m_instance_buffer.data(),
						GL_STATIC_DRAW);
			}
		}
	}

	if (m_use_ARB_vertex_attrib_binding) {
		glBindVertexBuffer(1, /*binding point */
			txt.m_gl_buffer,
			0, /* offset */
			sizeof(text::glyph_instance) /* stride */);
	} else {
		glBindBuffer(GL_ARRAY_BUFFER, txt.m_gl_buffer);

		glVertexAttribPointer(VBOX_LOC,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(text::glyph_instance),
			(void *)offsetof(text::glyph_instance, v_bounds));

		glVertexAttribPointer(COLOR_LOC,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(text::glyph_instance),
			(void *)offsetof(text::glyph_instance, color));

		glVertexAttribIPointer(UVW_LOC,
			3,
			GL_UNSIGNED_INT,
			sizeof(text::glyph_instance),
			(void *)offsetof(text::glyph_instance, uvw));
	}
	glUniform2f(m_disp_loc, dx, dy);

	glDrawArrays(GL_POINTS, 0, num_chars);
}

text_builder::text_builder(const font_const_ptr &font, color color) :
	m_prev_index(-1)
{
	m_color_stack.push_back(color);
	m_font_stack.push_back(font);
	m_text = new text(m_font_stack.back(),
		m_color_stack.back().r,
		m_color_stack.back().g,
		m_color_stack.back().b,
		m_color_stack.back().a, "");
}

text *text_builder::get_text()
{
	gen_glyphs();
	text *ret = m_text;
	m_text = new text(m_font_stack.back(),
		m_color_stack.back().r,
		m_color_stack.back().g,
		m_color_stack.back().b,
		m_color_stack.back().a, "");
	return ret;
}

text_builder &text_builder::operator<<(font_const_ptr font)
{
	gen_glyphs();
	m_font_stack.push_back(font);
	m_prev_index = -1;
	return *this;
}

text_builder &text_builder::operator<<(const color &color)
{
	gen_glyphs();
	m_color_stack.push_back(color);
	return *this;
}

text_builder &pop_font(text_builder &t)
{
	t.gen_glyphs();
	if (t.m_font_stack.size() > 1) {
		t.m_font_stack.pop_back();
		t.m_prev_index = -1;
	}
	return t;
}

text_builder &pop_color(text_builder &t)
{
	t.gen_glyphs();
	if (t.m_color_stack.size() > 1)
		t.m_color_stack.pop_back();
	return t;
}

void text_builder::gen_glyphs()
{
	int c;
	m_font_stack.back()->select();
	while ((c = get()) != EOF) {
		m_text->append(m_font_stack.back(), m_color_stack.back(), c, m_prev_index);
	}
	clear();
}

}

namespace std {

gl_text::text_builder &endl(gl_text::text_builder &t)
{
	t.gen_glyphs();
	t.m_text->m_line_breaks.push_back(t.m_text->m_instance_buffer.size());
	return t;
}

};
