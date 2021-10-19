#include "selector.h"
#include "../graphics/opengl.h"

selectorhdl::selectorhdl(palettehdl &palette)
{
	type = "selector";

	program = palette.program("res/plot.vx", "res/plot.ft");
	size = 12.0;
}

selectorhdl::~selectorhdl()
{
}

void selectorhdl::prepare(vec2f inches)
{
	float width = size/(96.0*inches[1]);

	int j = 0;
	float curr = 1.0 - width;
	for (auto i = elems.begin(); i != elems.end(); i++, j++) {
		(*i)->position = vec2f(0.05/inches[0], 0.0);
		(*i)->scale = vec2f(1.0, 1.0);

		(*i)->position[1] = curr - width*0.2;
		(*i)->scale[1] = width*1.2;
		curr -= width;
	}
}

void selectorhdl::render()
{
	glUseProgram(program);
	int vertex_location = glGetAttribLocation(program, "vertex");

	static vec2f points[] = {
		vec2f(0.0, 0.0),
		vec2f(1.0, 0.0),
		vec2f(1.0, 1.0),
		vec2f(0.0, 1.0)
	};

	static int indices[] = {0, 1, 2, 3};
	
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2f)*4, (GLfloat*)points, GL_STATIC_DRAW);
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*4, (GLuint*)indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(vertex_location);
	glVertexAttribPointer(vertex_location, 2, GL_FLOAT, false, 0, 0);

	glUniform4f(glGetUniformLocation(program, "color"), 0.9, 0.9, 0.9, 1.0);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, 0);

	glLineWidth(8.0);
	glUniform4f(glGetUniformLocation(program, "color"), 0.6, 0.6, 0.6, 1.0);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0);
	glLineWidth(1.0);
	
	glDisableVertexAttribArray(vertex_location);

	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}
