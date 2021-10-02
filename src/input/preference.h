/*
 * preference.h
 *
 *  Created on: May 16, 2015
 *      Author: nbingham
 */

#include <math/geometry.h>

using namespace core;

#ifndef preference_h
#define preference_h

struct preference
{
	preference();
	preference(void *data, void (*function)(preference *, vec3f));
	~preference();

	void *data;
	void (*function)(preference*, vec3f);

	void operator()(vec3f value);
	bool is_valid();
};

#endif
