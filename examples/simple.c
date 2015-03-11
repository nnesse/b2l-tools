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

#include "gltext.h"
#include "glb_gl.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>


static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

#include <math.h>

int main(void)
{
	GLFWwindow* window;

	gltext_renderer_t renderer = gltext_renderer_new();

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(-1);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1024, 128, "Simple text output example", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);

	init_gl(3, 3);

	const char *charset = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'\"0123456789`~!@#$%^&*()_+;/?.>,<={}[]\\";
	struct gltext_font fonts[1];
	struct gltext_font_desc font_desc = {
		.typeface = gltext_renderer_get_typeface(renderer, "ttf/LiberationSans-Regular.ttf"),
		.width = 20,
		.height = 20,
		.charset = charset
	};
	if (!gltext_renderer_initialize(renderer, &font_desc, 1, fonts)) {
		glfwTerminate();
		exit(-1);
	}

	glfwSetKeyCallback(window, key_callback);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	glfwSwapInterval(1);


	while (!glfwWindowShouldClose(window)) {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		float mvp[16] = {
			2.0/width,0,0,0,
			0,-2.0/height,0,0,
			0,0,1,0,
			-1,0,0,1};
		
		const char *str = "The quick brown fox jumps over the lazy dog()'\"0123456789`~!@#$%^&*()_+;/?.>,<={}[]\\";
		struct gltext_glyph_instance *r = gltext_renderer_prepare_render(renderer, strlen(str));

		struct gltext_glyph *g_prev = NULL;
		float x_pos = 0;
		float y_pos = 0;
		struct gltext_color color = {
			.r = 1,
			.g = 1,
			.b = 1,
			.a = 1
		};
		while (*str) {
			struct gltext_glyph *g_cur = fonts[0].glyph_array + (*str);
			x_pos += gltext_get_advance(g_prev, g_cur);
			r->pos[0] = x_pos;
			r->pos[1] = y_pos;
			r->w = g_cur->w;
			r->color = color;
			r++;
			str++;
			g_prev = g_cur;
		}
		gltext_renderer_submit_render(renderer, mvp);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
