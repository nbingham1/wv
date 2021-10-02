#pragma once

#include <std/list.h>
#include <math/geometry.h>
#include "../engine/object.h"
#include "../graphics/palette.h"

using namespace core;

struct signalhdl
{
	string name;
	array<vec2f> data;
};

struct plothdl : objecthdl
{
	plothdl(palettehdl &palette);
	~plothdl();

	array<list<signalhdl>::iterator> signals;

	int program;

	array<vec3f> points;
	array<int> indices;

	void render(framehdl &frame);
};

