#pragma once

#include <std/list.h>
#include <math/geometry.h>
#include "elem.h"
#include "../graphics/palette.h"

using namespace core;

struct signalhdl
{
	string name;
	array<vec2f> data;
};

struct plothdl : elemhdl
{
	plothdl(palettehdl &palette);
	~plothdl();

	array<list<signalhdl>::iterator> signals;

	int program;

	array<vec3f> points;
	array<int> indices;

	void render(vec2i size);
};

