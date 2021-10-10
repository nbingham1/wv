#pragma once

#include <std/list.h>
#include <math/geometry.h>
#include "elem.h"
#include "../graphics/palette.h"

using namespace core;

struct datahdl
{
	string name;
	array<vec2f> values;
};

struct geometryhdl {
	array<vec2f> points;
	array<int> indices;
	vec4f color;
	
	void render(int program);
};

struct signalhdl {
	datahdl *data;
	geometryhdl curve;

	void prepare(vec2f offset, vec2f size);
	void render(int program);
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

	list<signalhdl> signals;

	vec2f offset;
	vec2f size;

	void prepare(vec2f inches);
	void render();
};


