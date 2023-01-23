#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "functions09.h"
#include "shader.h"
#include "camera.h"

//Settings
const unsigned int width = 800;
const unsigned int height = 600;

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

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

	Shader ourShader("vertex_shader.vs", "fragment_shader.fs");
	Shader lightBlockShader("light_cube.vs", "light_cube.fs");
	
	int VAO = bindBuffers();
	unsigned int diffMap = loadTexture("container2.png");
	unsigned int specMap = loadTexture("container2_specular.png");

	// shader configuration
	// --------------------
	ourShader.use();
	ourShader.setInt("mat.diffuse", 0);
	ourShader.setInt("mat.specular", 1);


	glm::mat4 model(0);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ourShader.use();
		ourShader.processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.setFloat("mat.shininess", 64.0f);

		ourShader.setVec3("circLight.ambient", 0.3f, 0.3f, 0.3f);
		ourShader.setVec3("circLight.diffuse", 0.6f, 0.6f, 0.6f);
		ourShader.setVec3("circLight.specular", 1.0f, 1.0f, 1.0f);

		ourShader.setFloat("circLight.constant", 1.0f);
		ourShader.setFloat("circLight.linear", 0.09f);
		ourShader.setFloat("circLight.quadratic", 0.032f);

		ourShader.setVec3("headLight.ambient", 0.00f, 0.05f, 0.00f);
		ourShader.setVec3("headLight.diffuse", 0.3f, 0.9f, 0.3f);
		ourShader.setVec3("headLight.specular", 0.7f, 1.0f, 0.7f);

		ourShader.setFloat("headLight.constant", 1.0f);
		ourShader.setFloat("headLight.linear", 0.09f);
		ourShader.setFloat("headLight.quadratic", 0.032f);

		ourShader.setFloat("headLight.cutOff", glm::cos(glm::radians(12.0f)));
		ourShader.setFloat("headLight.outerCutOff", glm::cos(glm::radians(15.0f)));
		ourShader.setVec3("headLight.direction", camera.Front);
	
		glm::vec2 cam_mov = mouse_offset(window);
		camera.ProcessMouseMovement(cam_mov.x, cam_mov.y);

		// camera/view transformation
		camera.ProcessKeyboard(window, deltaTime);

		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);

		ourShader.setMat("view", view);
		ourShader.setMat("projection", proj);

		// calc circle 
		float rad = 3.0;
		float speed = 0.5;
		float x = rad * cos(speed * currentFrame);
		float y = rad * sin(speed * currentFrame);

		lightPos = glm::vec3(x, 0, y);

		//Set properties for lighting 
		ourShader.setVec3("circLight.position", lightPos);
		ourShader.setVec3("headLight.position", camera.Position);
		ourShader.setVec3("viewPos", camera.Position);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specMap);


		// Draw cubes
		for (int i = 0; i < 9; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			ourShader.setMat("model", model);
			draw(VAO);
		}

		// Draw light cube
		lightBlockShader.use();
		lightBlockShader.setMat("projection", proj);
		lightBlockShader.setMat("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
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

