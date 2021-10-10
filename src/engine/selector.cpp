#include "selector.h"
#include "../graphics/opengl.h"

selectorhdl::selectorhdl(palettehdl &palette)
{
	type = "selector";

	program = palette.program("res/plot.vx", "res/plot.ft");
}

selectorhdl::~selectorhdl()
{
}

void selectorhdl::prepare(vec2f inches)
{
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
