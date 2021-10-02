/*
 * elem.cpp
 *
 *  Created on: Nov 11, 2014
 *      Author: nbingham
 */

#include "elem.h"
#include "canvas.h"

elemhdl::elemhdl()
{
	type = "elem";
	selected = false;

	position = vec2f(0.0, 0.0);
	scale = vec2f(1.0, 1.0);
}

elemhdl::~elemhdl()
{

}

void elemhdl::init(canvashdl &canvas)
{
}

void elemhdl::prepare(canvashdl &canvas)
{
}

void elemhdl::render(vec2i size)
{
}

void elemhdl::view(vec2i parent_offset, vec2i parent_size) {
	vec2i offset = parent_offset + parent_size*position;
	vec2i size = parent_size*scale;

	glViewport(offset[0], offset[1], size[0], size[1]);
	render(size);

	for (list<elemhdl*>::iterator i = elems.begin(); i != elems.end(); i++) {
		if (*i != NULL) {
			(*i)->view(offset, size);
		}
	}
}
