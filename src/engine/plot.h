#pragma once

#include <std/list.h>
#include <math/geometry.h>
#include "elem.h"
#include "data.h"
#include "../graphics/palette.h"

using namespace core;

struct geometryhdl {
	array<vec2f> points;
	array<int> indices;
	vec4f color;
	
	void render(int program);
};

struct signalhdl {
	signalhdl();
	signalhdl(datahdl *data);
	~signalhdl();

	datahdl *data;
	vec4f color;
	
	void render(int program, vec2f offset, vec2f size);
};

struct gridhdl {
	geometryhdl grid;
	geometryhdl axes;

	void prepare(vec2f inches, vec2f offset, vec2f size);
	void render(int program);
};

struct plothdl : elemhdl
{
	plothdl(palettehdl &palette);
	~plothdl();

	int program;
	int plot_program;

	list<signalhdl> signals;

	vec2f offset;
	vec2f size;

	void prepare(vec2f inches);
	void render();
};


