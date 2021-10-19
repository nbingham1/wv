#include "textbox.h"
#include "../graphics/opengl.h"

textboxhdl::textboxhdl(palettehdl &palette, string content)
{
	type = "textbox";

	wrap = false;
	size = 12.0;
	color = vec4f(0.0, 0.0, 0.0, 1.0);
	this->content = content;

	font.load_ttf(palette, "res/FreeSerif.ttf", 48);
}

textboxhdl::~textboxhdl()
{
}

void textboxhdl::prepare(vec2f inches)
{
	vec2f scale = 96.0f*inches;

	points.clear();
	indices.clear();
	points.reserve(4*content.size());
	indices.reserve(6*content.size());

	float advance = 0.0;
	int row = 0;
	int index = 0;
	for (int i = 0; i < content.size(); i++) {
		if (advance > 0.0 and (content[i] == '\n' or content[i] == '\r')) {
			advance = 0.0;
			row += 1;
		} else {
			if (wrap) {
				float test = advance;
				for (int j = i; advance > 0.0 and j < content.size() and content[j] != ' ' and content[j] != '\t' and content[j] != '\r' and content[j] != '\n'; j++) {
					test += font.chars[content[j]].advance;
					if (size*test/scale[0] > 1.0) {
						advance = 0.0;
						row += 1;
					}
				}
			}

			characterhdl c = font.chars[content[i]];

			float offset = 1.0 - float(row+1)*size/scale[1];
			float x0 = size*(advance + c.bearing[0])/scale[0];
			float x1 = size*(advance + c.bearing[0] + c.size[0])/scale[0];
			float y0 = size*(c.bearing[1])/scale[1] + offset;
			float y1 = size*(c.bearing[1] + c.size[1])/scale[1] + offset;

			float u0 = c.origin[0];
			float u1 = c.origin[0] + c.span[0];
			float v0 = c.origin[1];
			float v1 = c.origin[1] + c.span[1];

			points.push_back(vec4f(x0, y0, u0, v0));
			points.push_back(vec4f(x1, y0, u1, v0));
			points.push_back(vec4f(x1, y1, u1, v1));
			points.push_back(vec4f(x0, y1, u0, v1));
			advance += c.advance;	
			

			indices.push_back(4*index + 0);
			indices.push_back(4*index + 1);
			indices.push_back(4*index + 2);
			indices.push_back(4*index + 0);
			indices.push_back(4*index + 2);
			indices.push_back(4*index + 3);
			index += 1;
		}
	}
}

void textboxhdl::render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

	glUseProgram(font.program);
	int vertex_location = glGetAttribLocation(font.program, "vertex");

	glUniform4f(glGetUniformLocation(font.program, "color"), color[0], color[1], color[2], color[3]);
	glUniform1i(glGetUniformLocation(font.program, "tex_0"), 0);

	font.glyphs.bind();

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec4f)*points.size(), (GLfloat*)points.data, GL_STATIC_DRAW);
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), (GLuint*)indices.data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(vertex_location);
	glVertexAttribPointer(vertex_location, 4, GL_FLOAT, false, 0, 0);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(vertex_location);

	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}
