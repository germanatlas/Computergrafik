#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "functions11.h"
#include "shader.h"
#include "camera.h"
#include "shader_transform.h"


//Settings
const unsigned int width = 800;
const unsigned int height = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


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

	
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	std::vector<float> input = {0.25f, 0.5f, 0.75f, 1.0f, 1.25f, 1.5f, 1.75f , 2.0f, 2.5f, 3.0f};
	std::vector<float> output(input.size());
	ShaderTransform tf_shader = ShaderTransform(&input, &output);
	std::cout << "Input:\tOutput:\n";
	for (int i = 0; i < input.size(); i++) {
		std::cout << input[i] << "\t" << output[i] << "\n";
	}

	ShaderTransform tf_shader2 = ShaderTransform();

	Shader shaderProgram("11/vertex_shader.vs", "11/fragment_shader.fs");
	
	glPointSize(10);
	while (!glfwWindowShouldClose(window)) {
	
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.use();
		shaderProgram.processInput(window);
		shaderProgram.refreshUnifroms();
		glBindVertexArray(tf_shader2.VAO);

		glDrawArrays(GL_POINTS, 0, 150);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} glfwTerminate();
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

