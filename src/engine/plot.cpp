#include "plot.h"
#include "../graphics/opengl.h"

float compute_ticks_per_line(float inches, float size) {
	static const float sep[] = {1.0, 2.0, 5.0};
	static const int len = 3;
	static const float inches_per_line_floor = 0.1;

	float inches_per_tick = inches / size;
	float lines_per_tick = inches_per_tick / inches_per_line_floor;

	float exp_estimate = floor(log10(lines_per_tick));
	float sig_estimate = lines_per_tick/pow(10, exp_estimate);

	float e = exp_estimate;
	float s = sig_estimate;
	float dist = 10.0;
	for (int i = 0; i < len; i++) {
		if (abs(sig_estimate - sep[i]) < dist and sig_estimate > sep[i]) {
			s = sep[i];
			e = exp_estimate;
			dist = abs(sig_estimate - sep[i]);
		}

		if (abs(sig_estimate/10.0 - 1.0/sep[i]) < dist and sig_estimate/10.0 > 1.0/sep[i]) {
			s = 1.0/sep[i];
			e = exp_estimate+1.0;
			dist = abs(sig_estimate/10.0 - 1.0/sep[i]);
		}
	}

	return 1.0 / (s*pow(10, e));
}

vec2f compute_ticks_per_line(vec2f inches, vec2f size) {
	return vec2f(compute_ticks_per_line(inches[0], size[0]), compute_ticks_per_line(inches[1], size[1]));
}

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

signalhdl::signalhdl() {
	data = nullptr;
	color = vec4f(1.0, 1.0, 1.0, 1.0);
}

signalhdl::signalhdl(datahdl *data) {
	this->data = data;
	color = vec4f(1.0, 1.0, 1.0, 1.0);
}

signalhdl::~signalhdl() {
}

void signalhdl::render(int program, vec2f offset, vec2f size) {
	glUseProgram(program);
	glUniform4f(glGetUniformLocation(program, "color"), color[0], color[1], color[2], color[3]);
	glUniform2f(glGetUniformLocation(program, "offset"), offset[0], offset[1]);
	glUniform2f(glGetUniformLocation(program, "scale"), size[0], size[1]);

	// Find the locations of the vertex, normal, and texcoord variables in the shader
	int vertex_location = glGetAttribLocation(program, "vertex");

	if (data != nullptr and data->points.size() > 0 and data->indices.size() > 0)
	{
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec2f)*data->points.size(), (GLfloat*)data->points.data, GL_STATIC_DRAW);
		GLuint ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*data->indices.size(), (GLuint*)data->indices.data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(vertex_location);
		glVertexAttribPointer(vertex_location, 2, GL_FLOAT, false, 0, 0);
		glDrawElements(GL_LINE_STRIP, data->indices.size(), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(vertex_location);

		glDeleteBuffers(1, &ibo);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}
}

void gridhdl::prepare(vec2f inches, vec2f offset, vec2f size) {
	axes.points.clear();
	axes.indices.clear();

	axes.points.reserve(3);
	axes.indices.reserve(4);
	axes.color = vec4f(1.0, 1.0, 1.0, 1.0);

	vec2f label_size = 0.5f/inches;

	axes.points.push_back(label_size);
	axes.points.push_back(vec2f(1.0, label_size[1]));
	axes.points.push_back(vec2f(label_size[0], 1.0));
	axes.indices.push_back(0);
	axes.indices.push_back(1);
	axes.indices.push_back(0);
	axes.indices.push_back(2);

	grid.points.clear();
	grid.indices.clear();

	vec2f ticks_per_line = compute_ticks_per_line(inches - label_size, size);

	cout << ticks_per_line << " ticks per line" << endl;

	vec2i n = vec2i(size/ticks_per_line) - vec2i(2, 2);
	cout << n << "/" << size << endl;

	grid.points.reserve(2*n[0] + 2*n[1]);
	grid.indices.reserve(2*n[0] + 2*n[1]);
	grid.color = vec4f(0.25, 0.25, 0.25, 1.0);

	for (int i = 0; i < n[0]; i++) {
		grid.points.push_back(vec2f(ticks_per_line[0] * (i+1)/size[0] + label_size[0], label_size[1]));
		grid.points.push_back(vec2f(ticks_per_line[0] * (i+1)/size[0] + label_size[0], 1.0));
		grid.indices.push_back(i*2);
		grid.indices.push_back(i*2+1);
	}

	for (int i = 0; i < n[1]; i++) {
		grid.points.push_back(vec2f(label_size[0], ticks_per_line[1] * (i+1)/size[1] + label_size[1]));
		grid.points.push_back(vec2f(1.0, ticks_per_line[1] * (i+1)/size[1] + label_size[1]));
		grid.indices.push_back(i*2 + 2*n[0]);
		grid.indices.push_back(i*2+1 + 2*n[0]);
	}
}

void gridhdl::render(int program) {
	axes.render(program);
	grid.render(program);
}

plothdl::plothdl(palettehdl &palette)
{
	type = "plot";

	program = palette.program("res/ui.vx", "res/ui.ft");
	plot_program = palette.program("res/plot.vx", "res/plot.ft");
	offset = vec2f(0.0, 0.1);
	size = vec2f(1e7, 0.5);
}

plothdl::~plothdl()
{
}

void plothdl::prepare(vec2f inches)
{
	/*for (auto i = signals.begin(); i != signals.end(); i++) {
		i->prepare(offset, size);
	}*/
}

void plothdl::render()
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

	glUniform4f(glGetUniformLocation(program, "color"), 0.0, 0.0, 0.0, 1.0);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, 0);

	glLineWidth(8.0);
	glUniform4f(glGetUniformLocation(program, "color"), 0.6, 0.6, 0.6, 1.0);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0);
	glLineWidth(1.0);
	
	glDisableVertexAttribArray(vertex_location);

	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	for (auto i = signals.begin(); i != signals.end(); i++) {
		i->render(plot_program, offset, size);
	}
}
