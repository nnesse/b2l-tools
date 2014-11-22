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

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

#include <iostream>

int main(void)
{
	GLFWwindow* window;

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

	gl_text::renderer renderer;
	const char *charset = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ(),.!0123456789";
	std::vector<gl_text::font_const_ptr> fonts;
	std::vector<gl_text::font_desc> font_desc = {
		{
			.typeface = renderer.get_typeface("ttf/LiberationSans-Regular.ttf"),
			.width = 20,
			.height = 20,
			.charset = charset
		}, {
			.typeface = renderer.get_typeface("ttf/LiberationSans-Regular.ttf"),
			.width = 50,
			.height = 50,
			.charset = charset
		}
	};
	if (!renderer.initialize(font_desc, fonts)) {
		glfwTerminate();
		exit(-1);
	}


	renderer << "The quick brown fox jumps over the lazy dog 0123456789 ()." << std::endl
		<< "Testing numbers ("
		<< 3.14159 << ", " << 11 << ", ...), "
		<< gl_text::color(0,1,0,1) << "different colors" << gl_text::pop_color
		<< ", and multiple font "
		<< fonts[1] << gl_text::color(1,0,0,1)
		<< "sizes"
		<< gl_text::pop_color << gl_text::pop_font << "."
		<< std::endl;
	gl_text::text *built_text = renderer.get_text();

	glfwSetKeyCallback(window, key_callback);

#if GLTEXT_USE_GLEW
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
#else
	glbindify::glEnable(GL_BLEND);
	glbindify::glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
#endif

	glfwSwapInterval(0);

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

		built_text->layout(width, height, 0, 0);
		renderer.render(*built_text, 0, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
