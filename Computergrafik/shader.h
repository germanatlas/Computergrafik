﻿#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>; // include glad to get all the required OpenGL headers 
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
	char* vertexPathShader; char* fragmentPathShader;
public:
	// the program ID
	unsigned int ID;

	// constructor reads and builds the shader
	void refresh() {
		glDeleteProgram(ID);
		init(vertexPathShader, fragmentPathShader);
	}

	void init(const char* vertexPath, const char* fragmentPath)
	{
		setVertexPath(vertexPath); setFragmentPath(fragmentPath);

		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit); fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file抯 buffer contents into streams 
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();


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
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setVertexPath(const char* vertexPath) {
		int len = strlen(vertexPath) + 1;
		vertexPathShader = new char[len];
		strcpy_s(vertexPathShader, len, vertexPath);
	}
	void setFragmentPath(const char* fragmentPath) {
		int len = strlen(fragmentPath) + 1; fragmentPathShader = new char[len];
		strcpy_s(fragmentPathShader, len, fragmentPath);
	}
	void refreshUnifroms() {
		// insert code here
	}

	int offset_X = 0;
	int offset_Y = 0;
	void processInput(GLFWwindow* window) {

		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
			refresh();
		// insert code here
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
			std::cout << "FUCK THIS SHIT" << std::endl;
			refresh();
		}
		
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
			std::cout << "I HATE MY LIFE" << std::endl;
			refresh();
		}
	}
};
#endif
