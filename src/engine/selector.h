#pragma once

#include <std/list.h>
#include <math/geometry.h>
#include "elem.h"
#include "../graphics/palette.h"

using namespace core;

struct selectorhdl : elemhdl
{
	selectorhdl(palettehdl &palette);
	~selectorhdl();

	int program;

	void prepare(vec2f inches);
	void render();
};


