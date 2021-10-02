/*
 * player.h
 *
 *  Created on: Nov 11, 2014
 *      Author: nbingham
 */

#include "../graphics/frame.h"
#include "../input/controller.h"

#ifndef player_h
#define player_h

struct playerhdl
{
	playerhdl();
	~playerhdl();

	vec4f viewport;

	void view(framehdl &frame, vec2i screen);

	float view_area();
	float view_width();
	float view_height();
};

#endif
