#pragma once

#include <std/list.h>
#include <math/geometry.h>
#include "elem.h"
#include "../graphics/palette.h"
#include "../graphics/font.h"

using namespace core;

struct textboxhdl : elemhdl
{
	textboxhdl(palettehdl &palette);
	~textboxhdl();

	fonthdl font;

	void prepare(vec2f inches);
	void render();
};


