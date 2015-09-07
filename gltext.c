#include "gltext.h"

#include <math.h>

#include "edtaa3func.c"

#define GLPLATFORM_GL_VERSION 33
#include "glplatform-glcore.h"

#include <ft2build.h>
#include FT_FREETYPE_H

enum vertex_attrib_locations {
	POS_LOC = 0,
	GLYPH_INDEX_LOC = 1
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
	GLuint atlas_texture;
	GLuint glyph_size_texture;
	GLuint glyph_size_texture_buffer;
	int max_char;
};

const struct gltext_glyph *gltext_get_glyph(gltext_font_t font_, char c)
{
	struct gltext_font *font = (struct gltext_font *)(font_);
	struct gltext_glyph *g;
	if (c > font->max_char) {
		return NULL;
	}
        g = font->glyph_array + c;
	if (!g->valid) {
		return NULL;
	}
	return g;
}

//
// renderer
//
struct renderer
{
	//
	// Freetype state
	//
	FT_Library ft_library;

	//
	// OpenGL state
	//
	GLuint glsl_program;
	GLuint fragment_shader;
	GLuint vertex_shader;
	GLuint geometry_shader;
	GLuint gl_vertex_array;
	GLuint stream_vbo;
	int sampler_loc;
	int color_loc;
	int glyph_size_sampler_loc;
	int mvp_loc;
	int num_chars;

	const char *charset;
	int max_char;

	bool initialized;
};

float gltext_get_advance(const struct gltext_glyph *prev, const struct gltext_glyph *next)
{
	float ret = 0;
	if (prev) {
		int d = prev->advance_x;
		if (next && prev->font == next->font) {
			FT_Vector delta;
			const struct gltext_font *font = prev->font;
			if (!FT_Get_Kerning(font->typeface,
					prev->typeface_index,
					next->typeface_index,
					FT_KERNING_DEFAULT,
					&delta)) {
				d += delta.x;
			}
		}
		ret += d/64.0;
	}
	return ret;
}

struct gltext_glyph_instance *gltext_renderer_prepare_render(gltext_renderer_t renderer_, gltext_font_t font_, int num_chars)
{
	struct gltext_font *font = (struct gltext_font *)(font_);
	struct renderer *inst = (struct renderer *)renderer_;
	if (!inst->initialized)
		return NULL;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, font->atlas_texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_BUFFER, font->glyph_size_texture);

	//Orphan previous buffer
	int buffer_size = sizeof(struct gltext_glyph_instance) * num_chars;
	glBindBuffer(GL_ARRAY_BUFFER, inst->stream_vbo);
	glBufferData(GL_ARRAY_BUFFER,
			buffer_size,
			NULL,
			GL_STREAM_DRAW);

	//Copy in new data
	struct gltext_glyph_instance * ret = (struct gltext_glyph_instance *) glMapBufferRange(
		GL_ARRAY_BUFFER,
		0, buffer_size,
		GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
	inst->num_chars = num_chars;
	return ret;
}

void gltext_renderer_submit_render(gltext_renderer_t renderer, const struct gltext_color *color, const float *mvp)
{
	struct renderer *inst = (struct renderer *)renderer;
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glUseProgram(inst->glsl_program);
	glBindVertexArray(inst->gl_vertex_array);
	glUniformMatrix4fv(inst->mvp_loc, 1, GL_FALSE, mvp);
	glUniform4fv(inst->color_loc, 1, (GLfloat *)color);
	glDrawArrays(GL_POINTS, 0, inst->num_chars);
}

gltext_renderer_t gltext_renderer_new(const char *charset)
{
	struct renderer *inst = malloc(sizeof(struct renderer));
	memset(inst, 0, sizeof(*inst));
	inst->ft_library = NULL;
	inst->glsl_program = 0;
	inst->fragment_shader = 0;
	inst->vertex_shader = 0;
	inst->geometry_shader = 0;
	inst->initialized = false;
	inst->charset = charset;
	FT_Init_FreeType(&inst->ft_library);

	int max_char = 0;
	for (const char *c = inst->charset; *c; c++)
		if (*c > max_char)
			max_char = *c;

	if ('\n' > max_char)
		max_char = '\n';
	inst->max_char = max_char;

	return inst;
}

void gltext_renderer_free(gltext_renderer_t renderer)
{
	struct renderer *inst = (struct renderer *)renderer;
	if (inst->fragment_shader)
		glDeleteShader(inst->fragment_shader);
	if (inst->geometry_shader)
		glDeleteShader(inst->geometry_shader);
	if (inst->vertex_shader)
		glDeleteShader(inst->vertex_shader);
	if (inst->glsl_program)
		glDeleteProgram(inst->glsl_program);
	if (inst->ft_library)
		FT_Done_FreeType(inst->ft_library);
	free(inst);
}

gltext_typeface_t gltext_renderer_get_typeface(gltext_renderer_t renderer, const char *path)
{
	FT_Face face;
	struct renderer *inst = (struct renderer *)renderer;
	int error = FT_New_Face(inst->ft_library, path, 0, &face);
	if (error) {
		return NULL;
	}
	return face;
}

static bool init_program(struct renderer *inst)
{
	const char *vertex_shader_text =
		"#version 330\n"
		"layout (location = 0) in vec2 pos_v;\n"
		"layout (location = 1) in int glyph_index_v;\n"
		"layout (location = 2) in vec4 color_v;\n"
		"out vec2 pos;\n"
		"out int glyph_index;\n"
		"void main()\n"
		"{\n"
			"pos = pos_v;\n"
			"glyph_index = glyph_index_v;\n"
			"gl_Position = vec4(0, 0, 1, 1);\n"
		"}\n";

	const char *geometry_shader_text =
		"#version 330\n"
		"layout(points) in;\n"
		"layout(triangle_strip, max_vertices=4) out;\n"
		"in vec2 pos[1];\n"
		"in int glyph_index[1];\n"
		"uniform mat4 mvp;\n"
		"uniform isamplerBuffer glyph_size_sampler;\n"
		"out vec3 texcoord_f;\n"
		"\n"
		"void genVertex(vec2 ul, vec2 corner, vec2 size, vec3 texcoord)\n"
		"{\n"
			"gl_Position = mvp * vec4((ul - vec2(8, 8) + (corner * size)), 0, 1);\n"
			"texcoord_f = texcoord + vec3(corner * size, 0);\n"
			"EmitVertex();\n"
		"}\n"
		"\n"
		"void main()\n"
		"{\n"
			"if (glyph_index[0] >= 0) {\n"
				"vec4 glyph_metrics = texelFetch(glyph_size_sampler, glyph_index[0]);\n"
				"vec2 size = glyph_metrics.xy + vec2(16,16);\n"
				"vec2 ul = pos[0] + vec2(glyph_metrics.z, -glyph_metrics.w);\n"
				"vec3 texcoord = vec3(0, 0, glyph_index[0]);\n"
				"genVertex(ul, vec2(0, 0), size, texcoord);\n"
				"genVertex(ul, vec2(1, 0), size ,texcoord);\n"
				"genVertex(ul, vec2(0, 1), size, texcoord);\n"
				"genVertex(ul, vec2(1, 1), size, texcoord);\n"
				"EndPrimitive();\n"
			"}\n"
		"}\n";

	const char *fragment_shader_text =
		"#version 330\n"
		"uniform sampler2DArray sampler;\n"
		"uniform vec4 color;\n"
		"in vec3 texcoord_f;\n"
		"out vec4 frag_color;\n"
		"void main()\n"
		"{\n"
			"ivec3 tex_size = textureSize(sampler, 0);\n"
			"float D = texture(sampler, vec3(texcoord_f.xy/tex_size.xy, texcoord_f.z)).r - 0.50;\n"
			"float aastep = length(vec2(dFdx(D), dFdy(D)));\n"
			"float texel = smoothstep(-aastep, aastep, D);\n"
			"frag_color = color * vec4(texel);\n"
		"}\n";

	GLint success;
	glGenVertexArrays(1, &inst->gl_vertex_array);
	glBindVertexArray(inst->gl_vertex_array);

	inst->geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(inst->geometry_shader, 1, (const char **)&geometry_shader_text, NULL);
	glCompileShader(inst->geometry_shader);
	glGetShaderiv(inst->geometry_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char info_log[1000];
		glGetShaderInfoLog(inst->geometry_shader, sizeof(info_log), NULL, info_log);
		printf("renderer: Geometry shader compile failed\n%s", info_log);
		glDeleteShader(inst->geometry_shader);
		inst->geometry_shader = 0;
		return false;
	}

	inst->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(inst->fragment_shader, 1, (const char **)&fragment_shader_text, NULL);
	glCompileShader(inst->fragment_shader);
	glGetShaderiv(inst->fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char info_log[1000];
		glGetShaderInfoLog(inst->fragment_shader, sizeof(info_log), NULL, info_log);
		printf("renderer: Fragment shader compile failed\n%s", info_log);
		glDeleteShader(inst->fragment_shader);
		inst->fragment_shader = 0;
		glDeleteShader(inst->geometry_shader);
		inst->geometry_shader = 0;
		return false;
	}

	inst->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(inst->vertex_shader, 1, (const char **)&vertex_shader_text, NULL);
	glCompileShader(inst->vertex_shader);
	glGetShaderiv(inst->vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char info_log[1000];
		glGetShaderInfoLog(inst->vertex_shader, sizeof(info_log), NULL, info_log);
		printf("renderer: Vertex shader compile failed\n%s", info_log);
		glDeleteShader(inst->fragment_shader);
		inst->fragment_shader = 0;
		glDeleteShader(inst->vertex_shader);
		inst->vertex_shader = 0;
		glDeleteShader(inst->geometry_shader);
		inst->geometry_shader = 0;
		return false;
	}

	inst->glsl_program = glCreateProgram();
	glAttachShader(inst->glsl_program, inst->vertex_shader);
	glAttachShader(inst->glsl_program, inst->geometry_shader);
	glAttachShader(inst->glsl_program, inst->fragment_shader);
	glLinkProgram(inst->glsl_program);
	glGetProgramiv(inst->glsl_program, GL_LINK_STATUS, &success);
	if (!success) {
		char info_log[1000];
		glGetProgramInfoLog(inst->glsl_program, sizeof(info_log), NULL, info_log);
		printf("renderer: Program link failed\n%s", info_log);
		glDeleteShader(inst->fragment_shader);
		inst->fragment_shader = 0;
		glDeleteShader(inst->vertex_shader);
		inst->vertex_shader = 0;
		glDeleteProgram(inst->glsl_program);
		inst->glsl_program = 0;
		return false;
	}

	glEnableVertexAttribArray(GLYPH_INDEX_LOC);
	glEnableVertexAttribArray(POS_LOC);

	glGenBuffers(1, &inst->stream_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, inst->stream_vbo);

	glVertexAttribPointer(POS_LOC,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(struct gltext_glyph_instance),
		(void *)offsetof(struct gltext_glyph_instance, pos));

	glVertexAttribIPointer(GLYPH_INDEX_LOC,
		1,
		GL_UNSIGNED_INT,
		sizeof(struct gltext_glyph_instance),
		(void *)offsetof(struct gltext_glyph_instance, w));

	//Cache uniform locations
	inst->mvp_loc = glGetUniformLocation(inst->glsl_program, "mvp");
	inst->sampler_loc = glGetUniformLocation(inst->glsl_program, "sampler");
	inst->color_loc = glGetUniformLocation(inst->glsl_program, "color");
	inst->glyph_size_sampler_loc = glGetUniformLocation(inst->glsl_program, "glyph_size_sampler");

	glUseProgram(inst->glsl_program);
	glUniform1i(inst->sampler_loc, 0);
	glUniform1i(inst->glyph_size_sampler_loc, 1);
	return true;
}

gltext_font_t gltext_font_create(gltext_renderer_t renderer, gltext_typeface_t typeface_, int size)
{
	struct renderer *inst = (struct renderer *)renderer;

	if (!inst->ft_library)
		return false;

	//Create GLSL program if neccisary
	if (!inst->initialized)
		if (!init_program(inst))
			return false;
	inst->initialized = true;

	struct gltext_font *f = (struct gltext_font *)calloc(1, sizeof(struct gltext_font));

	f->size = size;
	f->typeface = typeface_;
	f->max_char = inst->max_char;
	FT_Face typeface = (FT_Face) f->typeface;

	int total_glyphs = strlen(inst->charset);

	if (!typeface)
		return false;

	f->glyph_array = calloc((inst->max_char + 1), sizeof(struct gltext_glyph));
	f->renderer = renderer;
	FT_Set_Pixel_Sizes(typeface, size, size);

	int max_dim = 0;

	for (const char *c = inst->charset; *c; c++) {
		struct gltext_glyph *g = f->glyph_array + (*c);
		int index = FT_Get_Char_Index(typeface, *c);
		FT_Load_Glyph(typeface, index, 0/* flags */);
		FT_Render_Glyph(typeface->glyph, FT_RENDER_MODE_NORMAL);
		g->bitmap_pitch = typeface->glyph->bitmap.pitch;
		g->bitmap_width = typeface->glyph->bitmap.width;
		g->bitmap_height = typeface->glyph->bitmap.rows;
		size_t image_size = g->bitmap_pitch * g->bitmap_height;
		g->bitmap_bits = (uint8_t *)malloc(image_size);
		memcpy(g->bitmap_bits, typeface->glyph->bitmap.buffer, image_size);
		g->left = typeface->glyph->bitmap_left;
		g->top = typeface->glyph->bitmap_top;
		g->advance_x = typeface->glyph->advance.x;
		g->advance_y = typeface->glyph->advance.y;
		g->font = f;
		g->typeface_index = index;
		g->valid = true;
		max_dim = g->bitmap_width > max_dim ? g->bitmap_width : max_dim;
		max_dim = g->bitmap_height > max_dim ? g->bitmap_height : max_dim;
	}

	int pot_size;

	max_dim += 16;

	if (max_dim < 16) {
		pot_size = 16;
	} else {
		pot_size = 1 << (32 - __builtin_clz(max_dim));
	}

	f->glyph_array['\n'].c = '\n';
	f->glyph_array['\n'].font = f;
	int w = 0;
	for (const char *c = inst->charset; *c; c++) {
		struct gltext_glyph *g = f->glyph_array + (*c);
		g->w = w++;
		g->font = f;
	}

	int texels_per_layer = pot_size * pot_size;
	uint8_t *atlas_buffer = (uint8_t *)calloc(total_glyphs, texels_per_layer);
	int8_t *glyph_size_array = (int8_t *)malloc(total_glyphs * sizeof(int16_t) * 4);
	int8_t *glyph_size_ptr = glyph_size_array;

	double *srcf = (double *)malloc(texels_per_layer * sizeof(double));
	short *distx = (short *)malloc(texels_per_layer * sizeof(short));
	short *disty = (short *)malloc(texels_per_layer * sizeof(short)) ;
	double *gx = (double *)malloc(texels_per_layer * sizeof(double));
	double *gy = (double *)malloc(texels_per_layer * sizeof(double));
	double *dist = (double *)malloc(texels_per_layer * sizeof(double));

	uint8_t *layer_ptr = atlas_buffer;
	for (const char *c = inst->charset; *c; c++) {
		struct gltext_glyph *g = f->glyph_array + (*c);
		uint8_t *dest = layer_ptr + (pot_size * 8) + 8;
		uint8_t *source = g->bitmap_bits;
		for (int i = 0; i < g->bitmap_height; i++) {
			memcpy(dest, source, g->bitmap_width);
			dest += pot_size;
			source += g->bitmap_pitch;
		}

		uint8_t *temp = layer_ptr;
		int index = 0;
		for (int i = 0; i < g->bitmap_height + 16; i++) {
			for (int j = 0; j < g->bitmap_width + 16; j++) {
				srcf[index++] = (temp[j]*1.0)/256;
			}
			temp += pot_size;
		}
		computegradient(srcf, g->bitmap_width + 16, g->bitmap_height + 16, gx, gy);
		edtaa3(srcf, gx, gy, g->bitmap_width + 16, g->bitmap_height + 16, distx, disty, dist);

		temp = layer_ptr;
		index = 0;
		for (int i = 0; i < g->bitmap_height + 16; i++) {
			for (int j = 0; j < g->bitmap_width + 16; j++) {
				float s = dist[index++];
				int val = 128 - s*16.0;
				if (val < 0) val = 0;
				if (val > 255) val = 255;
				temp[j] = val;
			}
			temp += pot_size;
		}
		*(glyph_size_ptr++) = (int8_t)g->bitmap_width;
		*(glyph_size_ptr++) = (int8_t)g->bitmap_height;
		*(glyph_size_ptr++) = (int8_t)g->left;
		*(glyph_size_ptr++) = (int8_t)g->top;
		layer_ptr += texels_per_layer;
	}

	free(srcf);
	free(distx);
	free(disty);
	free(gx);
	free(gy);
	free(dist);

	//
	//Setup glyph size texture buffer
	//
	glGenBuffers(1, &f->glyph_size_texture_buffer);
	glBindBuffer(GL_TEXTURE_BUFFER, f->glyph_size_texture_buffer);
	glBufferData(GL_TEXTURE_BUFFER, total_glyphs * 4, glyph_size_array, GL_STATIC_DRAW);
	glGenTextures(1, &f->glyph_size_texture);
	glBindTexture(GL_TEXTURE_BUFFER, f->glyph_size_texture);
	glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA8I, f->glyph_size_texture_buffer);
	free(glyph_size_array);

	//
	// Allocate and altas texture and setup texture filtering
	//
	glGenTextures(1, &f->atlas_texture);
	glBindTexture(GL_TEXTURE_2D_ARRAY, f->atlas_texture);
	glTexImage3D(GL_TEXTURE_2D_ARRAY,
		0, /* layer */
		GL_R8,
		pot_size, pot_size, total_glyphs /* uvw size */,
		0, /* border */
		GL_RED,
		GL_UNSIGNED_BYTE,
		atlas_buffer);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
	free(atlas_buffer);
	return f;
}


bool gltext_font_free(gltext_font_t font_)
{
	struct gltext_font *font = (struct gltext_font *)(font_);
	glDeleteBuffers(1, &font->glyph_size_texture_buffer);
	glDeleteTextures(1, &font->glyph_size_texture);
	glDeleteTextures(1, &font->atlas_texture);
	free(font);
}
