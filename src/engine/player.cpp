/*
 * player.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: nbingham
 */

#include "player.h"
#include "graphics/opengl.h"

playerhdl::playerhdl()
{
}

playerhdl::~playerhdl()
{
}

void playerhdl::view(framehdl &frame, vec2i screen)
{
	glViewport(screen[0]*viewport[0],
			   screen[1]*viewport[1],
			   screen[0]*viewport[2],
			   screen[1]*viewport[3]);
}

