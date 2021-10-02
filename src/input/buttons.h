/*
 * buttons.h
 *
 *  Created on: May 16, 2015
 *      Author: nbingham
 */

#include <std/array.h>
#include <std/map.h>
#include "preference.h"

using namespace core;

#ifndef buttons_h
#define buttons_h

struct buttonshdl
{
	buttonshdl();
	~buttonshdl();

	array<int> pressed;
	map<int, preference> control;

	void press(int button);		// handle button press event
	void release(int button);	// handle button release event
	bool get(int button);		// get current state of button
	void set(int button, bool value);

	void reset();				// reset all button states to released
};

#endif
