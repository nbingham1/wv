/*
 * object.cpp
 *
 *  Created on: Nov 11, 2014
 *      Author: nbingham
 */

#include "object.h"
#include "canvas.h"

objecthdl::objecthdl()
{
	type = "object";
	selected = false;

	position = vec3f(0, 0, 0);
}

objecthdl::~objecthdl()
{

}

void objecthdl::init(canvashdl &canvas)
{
}

void objecthdl::prepare(canvashdl &canvas)
{
}

void objecthdl::render(framehdl &frame)
{
}

