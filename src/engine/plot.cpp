#include "plot.h"
#include "../graphics/opengl.h"

plothdl::plothdl(palettehdl &palette)
{
	type = "plot";

	program = palette.program("res/plot.vx", "res/plot.ft");

	points.reserve(3);
	indices.reserve(4);

	points.push_back(vec2f(0.0, 0.0));
	points.push_back(vec2f(1.0, 0.0));
	points.push_back(vec2f(0.0, 1.0));
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(0);
	indices.push_back(2);
}

plothdl::~plothdl()
{
}

void plothdl::render(vec2i size)
{
	glUseProgram(program);

	glUniform4f(glGetUniformLocation(program, "color"), 1.0, 1.0, 1.0, 1.0);

	// Find the locations of the vertex, normal, and texcoord variables in the shader
	int vertex_location = glGetAttribLocation(program, "vertex");

	if (points.size() > 0)
	{
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec2f)*points.size(), (GLfloat*)points.data, GL_STATIC_DRAW);
		GLuint ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), (GLuint*)indices.data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(vertex_location);
		glVertexAttribPointer(vertex_location, 2, GL_FLOAT, false, 0, 0);
		glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(vertex_location);

		glDeleteBuffers(1, &ibo);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}
}
