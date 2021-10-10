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
#include "div.h"
#include "selector.h"

canvashdl::canvashdl()
{
}

canvashdl::~canvashdl()
{
	release();
}

void canvashdl::initialize(int w, int h, int dx, int dy)
{
	// Initialize Display
	screen[0] = w;
	screen[1] = h;
	dpi[0] = dx;
	dpi[1] = dy;

	// Initialize some OpenGL Settings
	glClearColor(0.95, 0.95, 0.95, 0.0);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	divhdl *hs = new divhdl(0, array_t<double>(1, 1.5));
	selectorhdl *s = new selectorhdl(palette);
	divhdl *vs = new divhdl(1, array<float>());
	vs->elems.push_back(new plothdl(palette));
	vs->elems.push_back(new plothdl(palette));
	vs->elems.push_back(new plothdl(palette));

	hs->elems.push_back(s);
	hs->elems.push_back(vs);

	ui.elems.push_back(hs);
	ui.generate(dpi, vec2i(0,0), screen);
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
	ui.generate(dpi, vec2i(0,0), screen);
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
