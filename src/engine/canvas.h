/*
 * canvas.h
 *
 *  Created on: Nov 24, 2013
 *      Author: nbingham
 */

#include <math/geometry.h>
#include <math/big.h>
#include "input/controller.h"
#include "graphics/palette.h"
#include "graphics/opengl.h"
#include "graphics/frame.h"

#include "elem.h"

using namespace core;

#ifndef canvas_h
#define canvas_h

struct canvashdl
{
	canvashdl();
	~canvashdl();

	palettehdl palette;

	vec2i screen;

	map<string, controllerhdl> devices;
	elemhdl ui;

	void initialize(int w, int h);
	void reshape(int w, int h);
	void release();

	void prepare();
	void render();

	void input();
};

#endif
