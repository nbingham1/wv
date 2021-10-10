#include "div.h"
#include "../graphics/opengl.h"

divhdl::divhdl(int direction, array<float> sizes)
{
	type = "div";
	this->direction = direction;
	this->sizes = sizes;
}

divhdl::~divhdl()
{
}

void divhdl::prepare(vec2f inches)
{
	int len = elems.size();

	int j = 0;
	float curr = 0.0;
	for (auto i = elems.begin(); i != elems.end(); i++, j++) {
		(*i)->position = vec2f(0.0, 0.0);
		(*i)->scale = vec2f(1.0, 1.0);

		float width = (1.0-curr)/float(len - j);
		if (j < sizes.size()) {
			width = sizes[j]/inches[direction];
		}

		(*i)->position[direction] = curr;
		(*i)->scale[direction] = width;
		curr += width;
	}
}

void divhdl::render()
{
}
