/*
 * image.h
 *
 *  Created on: May 22, 2015
 *      Author: nbingham
 */

#pragma once

#include <std/string.h>
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace core;

struct imagehdl
{
	imagehdl();
	imagehdl(string filename);
	~imagehdl();

	string data;
	int bpp;
	int width;
	int height;
	int depth;

	bool load(string filename);

	bool load_tga(string filename);
};

