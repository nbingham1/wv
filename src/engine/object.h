/*
 * object.h
 *
 *  Created on: Nov 11, 2014
 *      Author: nbingham
 */

#include <math/geometry.h>
#include <std/string.h>
#include <math/big.h>
#include "graphics/frame.h"

using namespace core;

#ifndef object_h
#define object_h

struct canvashdl;

struct objecthdl
{
	objecthdl();
	virtual ~objecthdl();

	// dynamic type checking
	string type;

	vec3f position;

	// user interface
	bool selected;

	virtual void init(canvashdl &canvas);
	virtual void prepare(canvashdl &canvas);
	virtual void render(framehdl &frame);
};


#endif
