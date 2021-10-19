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
#include "selector.h"
#include "div.h"

using namespace core;

#ifndef canvas_h
#define canvas_h

struct canvashdl
{
	canvashdl();
	~canvashdl();

	palettehdl palette;

	vec2i screen;
	vec2i dpi;

	map<string, controllerhdl> devices;
	elemhdl ui;

	selectorhdl *signalSelector;
	divhdl *plotArea;

	void initialize(int w, int h, int dx, int dy);
	void reshape(int w, int h);
	void release();

	void prepare();
	void render();

	void input();

	void load(string filename);
};

#endif
