#include "plot.h"
#include "../graphics/opengl.h"

void geometryhdl::render(int program)
{
	glUniform4f(glGetUniformLocation(program, "color"), color[0], color[1], color[2], color[3]);

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

void signalhdl::prepare(vec2f offset, vec2f size) {
}

void signalhdl::render(int program) {
	curve.render(program);
}

void gridhdl::prepare(vec2f inches, vec2f offset, vec2f size) {
	axes.points.clear();
	axes.indices.clear();

	axes.points.reserve(3);
	axes.indices.reserve(4);
	axes.color = vec4f(1.0, 1.0, 1.0, 1.0);

	offset = 0.5f/inches;

	axes.points.push_back(offset);
	axes.points.push_back(vec2f(1.0, offset[1]));
	axes.points.push_back(vec2f(offset[0], 1.0));
	axes.indices.push_back(0);
	axes.indices.push_back(1);
	axes.indices.push_back(0);
	axes.indices.push_back(2);
}

void gridhdl::render(int program) {
	axes.render(program);
	grid.render(program);
}

plothdl::plothdl(palettehdl &palette)
{
	type = "plot";

	program = palette.program("res/plot.vx", "res/plot.ft");
}

plothdl::~plothdl()
{
}

void plothdl::prepare(vec2f inches)
{
	grid.prepare(inches, offset, size);
	for (auto i = signals.begin(); i != signals.end(); i++) {
		i->prepare(offset, size);
	}
}

void plothdl::render()
{
	glUseProgram(program);
	grid.render(program);
	for (auto i = signals.begin(); i != signals.end(); i++) {
		i->render(program);
	}
}
