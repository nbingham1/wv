#include "textbox.h"
#include "../graphics/opengl.h"

textboxhdl::textboxhdl(palettehdl &palette)
{
	type = "textbox";

	font.load_ttf(palette, "res/FreeSerif.ttf", 48);
}

textboxhdl::~textboxhdl()
{
}

void textboxhdl::prepare(vec2f inches)
{
}

void textboxhdl::render()
{
	glUseProgram(font.program);
	int vertex_location = glGetAttribLocation(font.program, "vertex");

	static vec4f points[] = {
		vec4f(0.0, 0.0, 0.0, 0.0),
		vec4f(1.0, 0.0, 1.0, 0.0),
		vec4f(1.0, 1.0, 1.0, 1.0),
		vec4f(0.0, 1.0, 0.0, 1.0)
	};

	static int indices[] = {0, 1, 2, 3};
	
	glUniform4f(glGetUniformLocation(font.program, "color"), 0.0, 0.0, 0.0, 1.0);
	glUniform1i(glGetUniformLocation(font.program, "tex_0"), 0);

	font.glyphs.bind();

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec4f)*4, (GLfloat*)points, GL_STATIC_DRAW);
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*4, (GLuint*)indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(vertex_location);
	glVertexAttribPointer(vertex_location, 4, GL_FLOAT, false, 0, 0);

	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(vertex_location);

	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}
