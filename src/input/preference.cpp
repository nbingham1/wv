/*
 * preference.cpp
 *
 *  Created on: May 16, 2015
 *      Author: nbingham
 */

#include "preference.h"
#include <std/list.h>

preference::preference()
{
	data = NULL;
	function = NULL;
}

preference::preference(void *data, void (*function)(preference *, vec3f))
{
	this->data = data;
	this->function = function;
}

preference::~preference()
{

}

void preference::operator()(vec3f value)
{
	if (function != NULL)
		function(this, value);
}

bool preference::is_valid()
{
	return function != NULL;
}
