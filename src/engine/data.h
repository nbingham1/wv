#pragma once

#include "textbox.h"

struct datahdl : textboxhdl
{
	datahdl(palettehdl &palette, string name);
	~datahdl();

	array<vec2f> points;
	array<int> indices;
};

