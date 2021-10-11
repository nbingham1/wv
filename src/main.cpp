/*
 * main.cpp
 * Blaze Game Engine v0.11
 *
 * Created by Ned Bingham on October 20, 2011.
 * Modified by Ned Bingham on October 20, 2011.
 * Copyright 2011 Sol Union. All rights reserved.
 *
 * Blaze Game Engine v0.11 is free software: you can redistribute
 * it and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * Blaze Game Engine v0.11 is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Blaze Game Engine v0.11.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <std/list.h>
#include <math/geometry.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#include "graphics/opengl.h"
#include "engine/canvas.h"

using namespace core;

pthread_t prepare_thread;
pthread_t display_thread;

bool windowed = true;

GLFWwindow *window = NULL;
canvashdl canvas;

void release(preference *pref, vec3f value)
{
	glfwSetWindowShouldClose(window, true);
}

void init(int w, int h)
{
	srand(time(0));

	char *dpi = getenv("DPI");
	int x, y;
	if (dpi == nullptr || sscanf(dpi, "%dx%d", &x, &y) != 2) {
		x = 96;
		y = 96;
	}

	canvas.initialize(w, h, x, y);
	canvas.devices.insert("mouse", controllerhdl(2));
	canvas.devices.insert("keyboard", controllerhdl());
	
	canvas.devices["keyboard"].buttons.control.insert(GLFW_KEY_ESCAPE, preference(NULL, release));
	canvas.devices["mouse"].axes[0].low = 0.25;
	canvas.devices["mouse"].axes[0].high = 0.75;
	canvas.devices["mouse"].axes[1].low = 0.25;
	canvas.devices["mouse"].axes[1].high = 0.75;
}

void *preparefunc(void *data)
{
	while (!glfwWindowShouldClose(window))
		canvas.prepare();

	pthread_exit(NULL);
	return NULL;
}

void *displayfunc(void *data)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	canvas.render();
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwWaitEvents();
		canvas.input();
	}
	return NULL;
}

void reshapefunc(GLFWwindow* window, int w, int h)
{
	canvas.reshape(w, h);
	canvas.prepare();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	canvas.render();
	glfwSwapBuffers(window);
}

void cursorfunc(GLFWwindow* window, double x, double y)
{
	static bool init = false;

	map<string, controllerhdl>::iterator mouse = canvas.devices.find("mouse");
	if (mouse != canvas.devices.end())
	{
		if (!init) {
			mouse->value.axes[0].warp((float)x/(float)canvas.screen[0]);
			mouse->value.axes[1].warp((float)y/(float)canvas.screen[1]);
			init = true;
		}
		mouse->value.axes[0].set((float)x/(float)canvas.screen[0]);
		mouse->value.axes[1].set((float)y/(float)canvas.screen[1]);
	}
}

void mousefunc(GLFWwindow* window, int button, int action, int mods)
{
	map<string, controllerhdl>::iterator mouse = canvas.devices.find("mouse");
	if (mouse != canvas.devices.end()) {
		mouse->value.buttons.set(button, action);
	}
}

void keyfunc(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	map<string, controllerhdl>::iterator keyboard = canvas.devices.find("keyboard");
	if (keyboard != canvas.devices.end()) {
		keyboard->value.buttons.set(key, action != 0);
	}
}

void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

int main(int argc, char **argv)
{
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	printf("%d %d\n", mode->width, mode->height);

	int width = 1024;
	int height = 768;

	glfwSetErrorCallback(error_callback);
	window = glfwCreateWindow(width, height, "Waveview", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error %s\n", glewGetErrorString(err));
		exit(1);
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, "Status: Using OpenGL %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "Status: Using GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, cursorfunc);
	glfwSetMouseButtonCallback(window, mousefunc);
	glfwSetKeyCallback(window, keyfunc);
	glfwSetWindowSizeCallback(window, reshapefunc);

	init(width, height);

	displayfunc(NULL);

	glfwDestroyWindow(window);
	glfwTerminate();
}
