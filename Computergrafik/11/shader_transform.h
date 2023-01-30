#ifndef SHADERTRANSFORM_H
#define SHADERTRANSFORM_H
#include <glad/glad.h>
#include <string>

class ShaderTransform {
private:
	const char* tf_shader_src = "#version 330 core\n"
		"layout (location = 0) in float inFloat;\n"
		"out float outFloat;\n"
		"void main() {\n"
		"outFloat = 0.5f * cos(inFloat) + 7;\n"
		"}\n";

	const char* vecfield_src = "#version 330 core\n"
		"layout(location = 0) in vec3 point;\n"
		"out vec3 res;\n"
		"vec3 vectorfield(vec3 p) {\n"
		"float x = p.x\n"
		"float y = p.y\n"
		"vec3 r = vec3(-0.25f * x + y, 0.25f - x * x, 0);\n"
		"return r;\n"
		"}\n"
		"void main() {\n"
		"float stepSize = 0.1;\n"
		"res = point + stepSize * vectorfield(point);\n"
		"}\n";
public:
	unsigned int VAO;
	ShaderTransform(const std::vector<float> *input, std::vector<float> *output) {
		this->init(input, output);
	}

	ShaderTransform() {
		this->init();
	}

	void init(const std::vector<float>* input, std::vector<float>* output) {

		float* in = (float*) malloc(input->size() * sizeof(float));
		float* out = (float*) malloc(output->size() * sizeof(float));
		for (int i = 0; i < input->size(); i++) {
			in[i] = input->at(i);
		}

		int tf_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(tf_shader, 1, &tf_shader_src, NULL);
		glCompileShader(tf_shader);

		unsigned int tf_Program = glCreateProgram();
		glAttachShader(tf_Program, tf_shader);
		
		const GLchar* feedbackVaryings[] = { "outFloat" };
		glTransformFeedbackVaryings(tf_Program, 1, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);

		glLinkProgram(tf_Program);
		glDeleteShader(tf_shader);
		glUseProgram(tf_Program);

		unsigned int tf_vao;
		glGenVertexArrays(1, &tf_vao);
		glBindVertexArray(tf_vao);

		unsigned int tf_vbo;

		glGenBuffers(1, &tf_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, tf_vbo);
		glBufferData(GL_ARRAY_BUFFER, input->size() * sizeof(float), in, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		unsigned int tf_vbo2;
		glGenBuffers(1, &tf_vbo2);
		glBindBuffer(GL_ARRAY_BUFFER, tf_vbo2);
		glBufferData(GL_ARRAY_BUFFER, input->size()*sizeof(float), NULL, GL_STATIC_READ);

		glEnable(GL_RASTERIZER_DISCARD);

		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tf_vbo2);

		glBeginTransformFeedback(GL_POINTS);
		glDrawArrays(GL_POINTS, 0, input->size());
		glEndTransformFeedback();

		glFlush();
		glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, output->size() * sizeof(float), out);

		for (int i = 0; i < output->size(); i++) {
			output->at(i) = out[i];
		}

		glDeleteProgram(tf_Program);
		glDeleteShader(tf_shader);
		glDeleteBuffers(1, &tf_vao);
		glDeleteBuffers(1, &tf_vbo);
		glDeleteBuffers(1, &tf_vbo2);
		glDisable(GL_RASTERIZER_DISCARD);

	}

	void init() {

		unsigned int tf_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(tf_shader, 1, &vecfield_src, NULL);
		glCompileShader(tf_shader);

		unsigned int tf_Program = glCreateProgram();
		glAttachShader(tf_Program, tf_shader);

		const GLchar* feedbackVaryings[] = { "res" };
		glTransformFeedbackVaryings(tf_Program, 1, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);

		glLinkProgram(tf_Program);
		glDeleteShader(tf_shader);
		glUseProgram(tf_Program);

		unsigned int tf_vao[2];
		glGenVertexArrays(2, tf_vao);
		unsigned int tf_vbo[2];
		glGenBuffers(2, tf_vbo);

		const int numPart = 150;
		float tf_data[3 * numPart];
		float tmp1, tmp2;
		srand(static_cast <unsigned> (time(0)));

		for (int i = 0; i < numPart; i++) {
			tmp1 = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f)));
			tmp2 = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f)));
			tf_data[i * 3 + 0] = tmp1;
			tf_data[i * 3 + 1] = tmp2;
			tf_data[i * 3 + 2] = 0;
		}

		for (int i = 0; i < 2; i++) {
			glBindVertexArray(tf_vao[i]);
			glBindBuffer(GL_ARRAY_BUFFER, tf_vbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(tf_data), tf_data, GL_DYNAMIC_COPY);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		for (int i = 0; i < 500; i++) {
			glBindVertexArray(tf_vao[i & 1]);
			glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tf_vbo[(i + 1) & 1]);
			glBeginTransformFeedback(GL_POINTS);
			glDrawArrays(GL_POINTS, 0, numPart);
			glEndTransformFeedback();
		}

		glFlush();

		//wenn es nicht initialisiert wird, wirft es errors
		unsigned int SSBO_time = 1;

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO_time);
		glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(tf_data), tf_data, GL_STATIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, SSBO_time);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

		glDeleteProgram(tf_Program);
		glDeleteShader(tf_shader);
		glBindVertexArray(0);

		glDeleteBuffers(1, &tf_vbo[1]);
		glDeleteVertexArrays(2, tf_vao);
		glDisable(GL_RASTERIZER_DISCARD);


		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, tf_vbo[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}
};
#endif