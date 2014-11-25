#include "gltext.hpp"

#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include <iostream>

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

gl_text::renderer renderer;
gl_text::text test_text;

static void char_callback(GLFWwindow* window, unsigned int key)
{
	renderer << &test_text << (char)key;
	renderer.flush();
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		if (key == GLFW_KEY_BACKSPACE) {
			test_text.pop();
		} else if (key == GLFW_KEY_ENTER) {
			renderer << &test_text << std::endl << gl_text::color(1,0,0,1) << "> " << gl_text::pop_color;
			renderer.flush();
		}
	}
	
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
#if GLTEXT_USE_GLEW
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
#else
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	window = glfwCreateWindow(1024, 256, "Terminal example", NULL, NULL);
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
	std::vector<gl_text::font_const_ptr> fonts;
	std::vector<gl_text::font_desc> font_desc = {
		{
			.typeface = renderer.get_typeface("ttf/LiberationSans-Regular.ttf"),
			.width = 20,
			.height = 20,
			.charset = charset
		}
	};
	if (!renderer.initialize(font_desc, fonts)) {
		glfwTerminate();
		exit(-1);
	}

	renderer << &test_text << fonts[0] << gl_text::color(1,1,1,1)
		<< gl_text::color(1,0,0,1) << "> " << gl_text::pop_color;
	renderer.flush();

	glfwSetKeyCallback(window, key_callback);
	glfwSetCharCallback(window, char_callback);

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
		test_text.set_layout(width, -1, -1, -1);
		int last_line_pos = test_text.get_line_pos(test_text.num_lines() - 1);
		if (last_line_pos > (height - 10)) {
			renderer.render(test_text, 0, (height - 10) - last_line_pos);
		} else {
			renderer.render(test_text, 0, 0);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
