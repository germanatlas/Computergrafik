#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "functions06.h"
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
	
	Shader ourShader;
	ourShader.init("vertex_shader.vs", "fragment_shader.fs");
	int VAO = bindBuffers();
	loadTexture(ourShader);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(5.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, 1.7f, -2.5f),
		glm::vec3(-5.5f, -2.0f, -12.3f),
		glm::vec3(2.2f, -2.0f, -3.5f)
	};

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();
		ourShader.processInput(window);
		
		for (int i = 0; i < 5; i++) {
			setMVP(ourShader, cubePositions[i]);
			draw(VAO);
		}
	
		glfwSwapBuffers(window);
		glfwPollEvents();

	} glfwTerminate();
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

