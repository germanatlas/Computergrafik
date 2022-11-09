#ifndef FUNCTIONS03_H
#define FUNCTIONS03_H
#include <glad/glad.h>; // include glad to get all the required OpenGL headers 
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class Shader
{
private:
	// Use to stote the shader path 
	char* vertexPathShader; char* fragmentPathShader;
public:
	// the program ID
	unsigned int ID;

	void refresh() {

		std::string vCode, fCode;
		std::ifstream vsFile, fsFile;

		try
		{
			vsFile.open(vertexPathShader);
			fsFile.open(fragmentPathShader);

			std::stringstream vsStream, fsStream;

			vsStream << vsFile.rdbuf();
			fsStream << fsFile.rdbuf();

			vsFile.close();
			fsFile.close();

			vCode = vsStream.str();
			fCode = fsStream.str();

		}
		catch (const std::exception&)
		{
			std::cout << "Error: File could not be read" << std::endl;
		}

		const char* vShaderCode = vCode.c_str();
		const char* fShaderCode = fCode.c_str();


		// 2. compile shaders
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];
		// vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		// print compile errors if any
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		// print compile errors if any
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};

		// shader Program
		this->ID = glCreateProgram();
		glAttachShader(this->ID, vertex);
		glAttachShader(this->ID, fragment);
		glLinkProgram(this->ID);
		// print linking errors if any
		glGetProgramiv(this->ID, GL_LINK_STATUS, &success); if (!success)
		{
			glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		// delete the shaders as they抮e linked into our program now and no longer necessery 
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}

	void init(const char* vertexPath, const char* fragmentPath)
	{

		vertexPathShader = (char*) vertexPath;
		fragmentPathShader = (char*) fragmentPath;

		std::string vCode, fCode;
		std::ifstream vsFile, fsFile;

		try
		{
			vsFile.open(vertexPathShader);
			fsFile.open(fragmentPathShader);

			std::stringstream vsStream, fsStream;

			vsStream << vsFile.rdbuf();
			fsStream << fsFile.rdbuf();

			vsFile.close();
			fsFile.close();

			vCode = vsStream.str();
			fCode = fsStream.str();

		}
		catch (const std::exception&)
		{
			std::cout << "Error: File could not be read" << std::endl;
		}

		const char* vShaderCode = vCode.c_str();
		const char* fShaderCode = fCode.c_str();


		// 2. compile shaders
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];
		// vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		// print compile errors if any
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		// print compile errors if any
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};

		// shader Program
		this->ID = glCreateProgram();
		glAttachShader(this->ID, vertex);
		glAttachShader(this->ID, fragment);
		glLinkProgram(this->ID);
		// print linking errors if any
		glGetProgramiv(this->ID, GL_LINK_STATUS, &success); if (!success)
		{
			glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		// delete the shaders as they抮e linked into our program now and no longer necessery 
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}
	void use()
	{
		glUseProgram(ID);
	}
	// utility uniform functions
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		//insert code here
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
	}

};


// new class not part of Shader anymore
// ------------------------------------------------------------------------
int offset_X = 0;
int offset_Y = 0;
void processInput(GLFWwindow* window, Shader& shaderProgram) {

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		shaderProgram.refresh();
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		offset_Y++;
		shaderProgram.setInt("offset_Y", offset_Y);
		std::cout << offset_X << " " << offset_Y << std::endl;
		shaderProgram.refresh();
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		offset_X--;
		shaderProgram.setInt("offset_X", offset_X);
		std::cout << offset_X << " " << offset_Y << std::endl;
		shaderProgram.refresh();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		offset_Y--;
		shaderProgram.setInt("offset_Y", offset_Y);
		std::cout << offset_X << " " << offset_Y << std::endl;
		shaderProgram.refresh();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		offset_X++;
		shaderProgram.setInt("offset_X", offset_X);
		std::cout << offset_X << " " << offset_Y << std::endl;
		shaderProgram.refresh();
	}
}


float vertices[] = {
1.0f, 1.0f, 0.0f, // top right
1.0f, -1.0f, 0.0f, // bottom right 
-1.0f, 1.0f, 0.0f, // top left
// second triangle
1.0f, -1.0f, 0.0f, // bottom right
-1.0f, -1.0f, 0.0f, // bottom left
-1.0f, 1.0f, 0.0f // top left
};
int bindbuffers() {
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return VAO;

}
void draw(int VAO) {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

#endif