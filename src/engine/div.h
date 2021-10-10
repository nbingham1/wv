#pragma once

#include <std/list.h>
#include <math/geometry.h>
#include "elem.h"
#include "../graphics/palette.h"

using namespace core;

struct divhdl : elemhdl
{
	divhdl(int direction, array<float> sizes);
	~divhdl();

	array<float> sizes;
	int direction;

	void prepare(vec2f inches);
	void render();
};


