/*
 * elem.h
 *
 *  Created on: Nov 11, 2014
 *      Author: nbingham
 */

#pragma once

#include <math/geometry.h>
#include <std/string.h>
#include <math/big.h>
#include <std/list.h>
#include "graphics/frame.h"

using namespace core;

struct canvashdl;

struct elemhdl
{
	elemhdl();
	virtual ~elemhdl();

	list<elemhdl*> elems;

	// dynamic type checking
	string type;

	vec2f position;
	vec2f scale;

	// user interface
	bool selected;

	virtual void init(canvashdl &canvas);
	virtual void prepare(canvashdl &canvas);
	virtual void render(vec2i size);

	void view(vec2i parent_offset, vec2i parent_size);
};

