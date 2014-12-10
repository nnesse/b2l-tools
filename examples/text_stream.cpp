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

#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>


#include <iostream>


static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
	GLFWwindow* window;

	gl_text::text test_text;
	gl_text::renderer renderer;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(-1);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#if GLTEXT_USE_GLEW
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
#else
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	window = glfwCreateWindow(1024, 256, "Simple text output example", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);

#if GLTEXT_USE_GLEW
	glewInit();
#else
	glbindify::gl::init();
#endif

	const char *charset = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ()'\"0123456789`~!@#$%^&*()_+;/?.>,<={}[]\\";
	const gl_text::font *fonts[4];
	gl_text::font_desc font_desc[4] = {
		{
			.typeface = renderer.get_typeface("ttf/LiberationSans-Regular.ttf"),
			.family = "LiberationSans",
			.style = gl_text::STYLE_REGULAR,
			.width = 35,
			.height = 35,
			.charset = charset
		}, {
			.typeface = renderer.get_typeface("ttf/LiberationSans-Italic.ttf"),
			.family = "LiberationSans",
			.style = gl_text::STYLE_ITALIC,
			.width = 35,
			.height = 35,
			.charset = charset
		}, {
			.typeface = renderer.get_typeface("ttf/LiberationSans-Bold.ttf"),
			.family = "LiberationSans",
			.style = gl_text::STYLE_BOLD,
			.width = 35,
			.height = 35,
			.charset = charset
		}, {
			.typeface = renderer.get_typeface("ttf/LiberationSans-BoldItalic.ttf"),
			.family = "LiberationSans",
			.style = (gl_text::STYLE_BOLD | gl_text::STYLE_ITALIC),
			.width = 35,
			.height = 35,
			.charset = charset
		}
	};
	if (!renderer.initialize(font_desc, 4, fonts)) {
		glfwTerminate();
		exit(-1);
	}

	gl_text::text_stream out(test_text, fonts[0], gl_text::color(1,1,1,1));

	out << "The quick brown fox jumps over the lazy dog 0123456789 ()." << std::endl
		<< "Testing numbers ("
		<< 3.14159 << ", " << 11 << ", ...), "
		<< gl_text::color(0,1,0,1) << "different colors" << gl_text::pop_color
		<< ", and "
		<< gl_text::color(1,0,0,1)
		<< fonts[1] << "multiple " << gl_text::pop_font
		<< gl_text::color(0.5,0,1,1) << fonts[2] << "font " << gl_text::pop_font << gl_text::pop_color
		<< fonts[3] << "styles" << gl_text::pop_font
		<< gl_text::pop_color
		<< "."
		<< std::endl;
	glfwSetKeyCallback(window, key_callback);

#if GLTEXT_USE_GLEW
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
#else
	glbindify::glEnable(GL_BLEND);
	glbindify::glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
#endif

	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window)) {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
#if GLTEXT_USE_GLEW
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
#else
		glbindify::glViewport(0, 0, width, height);
		glbindify::glClear(GL_COLOR_BUFFER_BIT);
#endif
		test_text.set_layout(width, height, 0, 0);
		renderer.render(test_text, 0, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
