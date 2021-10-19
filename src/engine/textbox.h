#pragma once

#include <std/list.h>
#include <math/geometry.h>
#include "elem.h"
#include "../graphics/palette.h"
#include "../graphics/font.h"

using namespace core;

struct textboxhdl : elemhdl
{
	textboxhdl(palettehdl &palette, string content = "");
	~textboxhdl();

	string content;
	
	bool wrap;
	float size;	
	vec4f color;
	fonthdl font;

	array<vec4f> points;
	array<int> indices;	

	void prepare(vec2f inches);
	void render();
};


