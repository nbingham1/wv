/*
 * font.h
 *
 *  Created on: May 22, 2015
 *      Author: nbingham
 */

#pragma once

#include <math/geometry.h>

#include <std/string.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "palette.h"

using namespace core;

struct characterhdl
{
	characterhdl();
	characterhdl(vec2f origin, vec2f span, vec2f size, vec2f bearing, float advance);
	~characterhdl();

	vec2f origin;
	vec2f span;

	vec2f size;
	vec2f bearing;
	float advance;
};

struct fonthdl
{
	fonthdl();
	fonthdl(palettehdl &palette, string filename);
	~fonthdl();

	unsigned int program;
	texturehdl glyphs;
	array<characterhdl> chars;

	bool load_ttf(palettehdl &palette, string filename, int char_size);
};

