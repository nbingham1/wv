/*
 * buttons.cpp
 *
 *  Created on: May 16, 2015
 *      Author: nbingham
 */

#include "buttons.h"
#include <std/file.h>

buttonshdl::buttonshdl()
{

}

buttonshdl::~buttonshdl()
{

}

void buttonshdl::press(int button)
{
	array<int>::iterator k = find_first(pressed, button);
	if (k == pressed.end())
	{
		pressed.push_back(button);

		map<int, preference>::iterator i = control.find(button);
		if (i != control.end())
			i->value(vec3f(1.0f, 1.0f, 0.0f));
	}
}

void buttonshdl::release(int button)
{
	array<int>::iterator k = find_first(pressed, button);
	if (k != pressed.end())
	{
		k.pop();

		map<int, preference>::iterator i = control.find(button);
		if (i != control.end())
			i->value(vec3f(0.0f, -1.0f, 0.0f));
	}
}

bool buttonshdl::get(int button)
{
	return contains(pressed, button);
}

void buttonshdl::set(int button, bool value)
{
	array<int>::iterator k = find_first(pressed, button);
	if (!value && k != pressed.end())
	{
		k.pop();

		map<int, preference>::iterator i = control.find(button);
		if (i != control.end())
			i->value(vec3f(0.0f, -1.0f, 0.0f));
	}
	else if (value && k == pressed.end())
	{
		pressed.push_back(button);

		map<int, preference>::iterator i = control.find(button);
		if (i != control.end())
			i->value(vec3f(1.0f, 1.0f, 0.0f));
	}
}

void buttonshdl::reset()
{
	pressed.clear();
}
