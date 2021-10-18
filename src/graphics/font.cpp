/*
 * font.cpp
 *
 *  Created on: May 22, 2015
 *      Author: nbingham
 */

#include "font.h"
#include <std/file.h>
#include <std/io.h>
#include <std/search.h>
#include "opengl.h"

using namespace core;

characterhdl::characterhdl()
{	
}

characterhdl::characterhdl(vec2f origin, vec2f span, vec2f size, vec2f bearing, float advance)
{
	this->origin = origin;
	this->span = span;
	this->size = size;
	this->bearing = bearing;
	this->advance = advance;
}

characterhdl::~characterhdl()
{
}

fonthdl::fonthdl()
{
}

fonthdl::fonthdl(palettehdl &palette, string filename)
{
	load_ttf(palette, filename, 48);
}

fonthdl::~fonthdl()
{

}

bool fonthdl::load_ttf(palettehdl &palette, string filename, int char_size)
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		cout << "ERROR::FREETYPE: Could not init FreeType Library" << endl;
		return false;
	}

	FT_Face face;
	if (FT_New_Face(ft, filename.c_str(), 0, &face))
	{
		cout << "ERROR::FREETYPE: Failed to load font" << endl;  
		return false;
	}

	FT_Set_Pixel_Sizes(face, 0, char_size);

	imagehdl img;
	img.bpp = 1;
	img.width = char_size*16;
	img.height = char_size*16;
	img.depth = 1;

	chars.reserve(256);
	img.data.reserve(img.width*img.height*img.bpp);
	img.data.count = img.width*img.height*img.bpp;
	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 16; x++) {
			if (FT_Load_Char(face, (char)(y*16 + x), FT_LOAD_RENDER))
			{
				cout << "ERROR::FREETYTPE: Failed to load Glyph" << endl;  
				return false;
			}

			chars.push_back_unsafe(characterhdl(
				vec2f(float(x)/16.0, float(y)/16.0), // origin
				vec2f(float(face->glyph->bitmap.width)/float(img.width), float(face->glyph->bitmap.rows)/float(img.height)), // span
				vec2f(float(face->glyph->bitmap.width)/float(char_size), float(face->glyph->bitmap.rows)/float(char_size)), // size
				vec2f(float(face->glyph->bitmap_left)/float(char_size), (float(face->glyph->bitmap_top) - float(face->glyph->bitmap.rows))/float(char_size)), // bearing
				float(face->glyph->advance.x)/float(char_size*64)
			));

			int s = 0;
			for (; s < face->glyph->bitmap.width; s++) {
				int t = 0;
				for (; t < face->glyph->bitmap.rows; t++) {
					img.data[(y*char_size + t)*img.width + (x*char_size + s)] = face->glyph->bitmap.buffer[(face->glyph->bitmap.rows - t-1)*face->glyph->bitmap.width + s];
				}

				for (; t < char_size; t++) {
					img.data[(y*char_size + t)*img.width + (x*char_size + s)] = 0;
				}
			}

			for (; s < char_size; s++) {
				for (int t = 0; t < char_size; t++) {
					img.data[(y*char_size + t)*img.width + (x*char_size + s)] = 0;
				}
			}
		}
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	program = palette.program("res/font.vx", "res/font.ft");
	glyphs = palette.texture(GL_TEXTURE_2D, filename, img);

	return true;
}

