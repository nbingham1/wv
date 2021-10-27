/*
 * canvas.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: nbingham
 */

#include "canvas.h"

#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <math/noise.h>
#include "plot.h"
#include "div.h"
#include "selector.h"
#include "textbox.h"
#include "data.h"

canvashdl::canvashdl()
{
	signalSelector = nullptr;
	plotArea = nullptr;
}

canvashdl::~canvashdl()
{
	release();
}

void canvashdl::initialize(int w, int h, int dx, int dy)
{
	// Initialize Display
	screen[0] = w;
	screen[1] = h;
	dpi[0] = dx;
	dpi[1] = dy;

	// Initialize some OpenGL Settings
	glClearColor(0.95, 0.95, 0.95, 0.0);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	divhdl *mainElem = new divhdl(0, array_t<double>(1, 1.0));
	signalSelector = new selectorhdl(palette);

	plotArea = new divhdl(1, array<float>());

	mainElem->elems.push_back(signalSelector);
	mainElem->elems.push_back(plotArea);

	ui.elems.push_back(mainElem);
	ui.generate(dpi, vec2i(0,0), screen);
}

void canvashdl::reshape(int w, int h)
{
	screen[0] = w;
	screen[1] = h;
}

void canvashdl::release()
{
	// Clean up the device list
	devices.clear();
}

void canvashdl::prepare()
{
	ui.generate(dpi, vec2i(0,0), screen);
}

void canvashdl::render()
{
	ui.view(vec2i(0, 0), screen);
}

void canvashdl::input()
{
	for (map<string, controllerhdl>::iterator i = devices.begin(); i != devices.end(); i++)
		i->value.update();
}

void canvashdl::load(string filename)
{
	file f(filename, file::r);

	array<datahdl*> data;

	int row = 0;
	array<string> cols;
	string col = " ";
	while (col.size() > 0) {
		cols.clear();
		col = " ";
		while (col.size() > 0 and col.back() != '\n' and col.back() != '\0' and col.back() != '\r') {
			col.clear();
			f.read_to(" \t\n\r\0", col);
			if (col.size() > 1) {
				cols.push_back(col.sub(0, -1));
			}
		}

		if (row == 0) {
			data.reserve(cols.size()-2);
			for (int i = 2; i < cols.size(); i++) {
				data.push_back(new datahdl(palette, cols[i]));
				signalSelector->elems.push_back(data.back());
				plotArea->elems.push_back(new plothdl(palette));
				((plothdl*)plotArea->elems.back())->signals.push_back(signalhdl(data.back()));
			}
		} else if (cols.size() > 1) {
			float t = atof(cols[1].c_str());
			if (t < min[0]) {
				min[0] = t;
			}
			if (t > max[0]) {
				max[0] = t;
			}
			for (int i = 2; i < cols.size(); i++) {
				float v = atof(cols[i].c_str());
				if (v < min[1]) {
					min[1] = v;
				}
				if (v > max[1]) {
					max[1] = v;
				}
				if (data[i-2] != nullptr) {
					data[i-2]->indices.push_back(data[i-2]->points.size());
					data[i-2]->points.push_back(vec2f(t, v));
				}
			}
		}

		row++;
	}

	f.close();	
}
