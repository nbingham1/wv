#include "graph.h"
#include "../graphics/opengl.h"

plothdl::plothdl(palettehdl &palette)
{
	type = "plot";

	program = palette.program("res/engine/white.vx", "res/engine/white.ft");

	float width = 1.0;
	float height = 1.0;
	float depth = 1.0;

	points.reserve(4);
	indices.reserve(6);

	points.push_back(vec3f(-width/2, -height/2, -depth/2));
	points.push_back(vec3f( width/2, -height/2, -depth/2));
	points.push_back(vec3f( width/2,  height/2, -depth/2));
	points.push_back(vec3f(-width/2,  height/2, -depth/2));
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);
}

plothdl::~plothdl()
{
}

void plothdl::render(framehdl &frame)
{
	glUseProgram(program);

	mat4f modelview_projection_matrix = frame.projection.value()*frame.modelview.value();
	glUniform4f(glGetUniformLocation(program, "color"), 1.0, 1.0, 1.0, 1.0);

	// Find the locations of the vertex, normal, and texcoord variables in the shader
	int vertex_location = glGetAttribLocation(program, "vertex");
	int mvp_matrix_location = glGetUniformLocation(program, "modelview_projection_matrix");

	//glUniformMatrix4fv(mvp_matrix_location, 1, true, (GLfloat*)&modelview_projection_matrix);

	if (points.size() > 0)
	{
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3f)*points.size(), (GLfloat*)points.data, GL_STATIC_DRAW);
		GLuint ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), (GLuint*)indices.data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(vertex_location);
		glVertexAttribPointer(vertex_location, 3, GL_FLOAT, false, 0, 0);
		glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(vertex_location);

		glDeleteBuffers(1, &ibo);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}
}
