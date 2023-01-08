#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "functions07.h"
#include "shader.h"



void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	const unsigned int width = 800;
	const unsigned int height = 600;


	GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL); if (window == NULL)
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
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	//for full rotation
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	while (!glfwWindowShouldClose(window)) {
		
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();

		float currentFrame = glfwGetTime();
		ourShader.deltaTime = currentFrame - ourShader.lastFrame;
		ourShader.lastFrame = currentFrame;

		ourShader.processInput(window);
		
		for (int i = 0; i < 9; i++)
		{
			setMVP(ourShader, cubePositions[i]);
			draw(VAO);
		}

		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSwapBuffers(window);
		glfwPollEvents();

	} glfwTerminate();
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

