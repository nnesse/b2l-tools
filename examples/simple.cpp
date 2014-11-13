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

#include "gl_3_3.hpp"
#include "gltext.hpp"

#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

using namespace glbindify;

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

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(-1);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1024, 256, "Simple text output example", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	
	glbindify::gl::init();

	gl_text::renderer renderer;

	std::vector<gl_text::font_desc> font_desc;
	std::vector<gl_text::font_const_ptr> fonts;
	font_desc.push_back({
		.typeface = renderer.get_typeface("ttf/LiberationSans-Regular.ttf"),
		.width = 35,
		.height = 35,
		.charset = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ().0123456789"
	});
	renderer.generate_fonts(font_desc, fonts);
	gl_text::text test_line(fonts[0], 1, 0, 0, 1, "The quick brown fox jumps over the lazy dog (). 0123456789");

	glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window)) {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		gl::Viewport(0, 0, width, height);
		gl::Clear(GL_COLOR_BUFFER_BIT);
		renderer.render(test_line, 0, 128);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
