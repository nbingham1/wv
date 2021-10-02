/*
 * canvas.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: nbingham
 */

#include "canvas.h"

#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <math/noise.h>
#include "plot.h"

canvashdl::canvashdl()
{
}

canvashdl::~canvashdl()
{
	release();
}

void canvashdl::initialize(int w, int h)
{
	// Initialize Display
	screen[0] = w;
	screen[1] = h;

	// Initialize some OpenGL Settings
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	ui.elems.push_back(new plothdl(palette));
}

void canvashdl::reshape(int w, int h)
{
	screen[0] = w;
	screen[1] = h;
}

void canvashdl::release()
{
	// Clean up the device list
	devices.clear();
}

void canvashdl::prepare()
{
	ui.prepare(*this);
}

void canvashdl::render()
{
	ui.view(vec2i(0, 0), screen);
}

void canvashdl::input()
{
	for (map<string, controllerhdl>::iterator i = devices.begin(); i != devices.end(); i++)
		i->value.update();
}
