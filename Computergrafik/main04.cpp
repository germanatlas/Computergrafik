#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "functions04.h"
#include "shader.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL); if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl; glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl; return -1;
	}

	//create Shader
	Shader ourShader;
	ourShader.init("vertex_shader.vs", "fragment_shader.fs");
	//bind Buffers
	int VAO = bindBuffers();
	//load texture to shader
	loadTexture(ourShader);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	while (!glfwWindowShouldClose(window)) {
		// use Shader
		ourShader.use();
		// process inputs and update uniforms
		ourShader.processInput(window);
		ourShader.refreshUnifroms();

		//draw vertex array 
		draw(VAO);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} glfwTerminate();
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

