#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "functions08.h"
#include "shader.h"
#include "camera.h"


// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//light
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

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

	Shader ourShader, lightBlockShader;
	ourShader.init("vertex_shader.vs", "fragment_shader.fs");
	lightBlockShader.init("light_cube.vs", "light_cube.fs");
	int VAO = bindBuffers();
	loadTexture(ourShader);

	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	glm::mat4 model(0);

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		lightPos.x = sin(glfwGetTime()) * 10.0f;
		lightPos.y = sin(glfwGetTime()) * 10.0f;
		lightPos.z = cos(glfwGetTime()) * 10.0f - 8;

		glm::vec2 cam_mov = mouse_offset(window);
		camera.ProcessMouseMovement(cam_mov.x, cam_mov.y);
		// camera/view transformation
		camera.ProcessKeyboard(window, deltaTime);

		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);


		ourShader.use();
		ourShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		ourShader.setVec3("lightColor", glm::vec3(1.0f));
		ourShader.setVec3("lightPos", lightPos);
		ourShader.setVec3("viewPos", camera.Position);
		ourShader.processInput(window);

		ourShader.setMat("view", view);
		ourShader.setMat("projection", proj);
		// Draw cubes
		for (int i = 0; i < 9; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			ourShader.setMat("model", model);
			draw(VAO);
		}

		lightBlockShader.use();
		lightBlockShader.setMat("projection", proj);
		lightBlockShader.setMat("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		lightBlockShader.setMat("model", model);
		draw(VAO);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} glfwTerminate();
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

