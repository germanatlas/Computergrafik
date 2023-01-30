#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "functions10.h"
#include "shader.h"
#include "camera.h"

#include "model.h"

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


	Shader ourShader("vertex_shader.vs", "fragment_shader.fs");

	Model terrain("terrain/terrain.obj");
	Model plane("plane/plane.obj");

	// shader configuration
	// --------------------
	ourShader.use();

	glm::mat4 model(0);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ourShader.processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glm::vec2 cam_mov = mouse_offset(window);
		camera.ProcessMouseMovement(cam_mov.x, cam_mov.y);

		// camera/view transformation
		camera.ProcessKeyboard(window, deltaTime);

		//View and proj matrix
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);

		ourShader.setMat("view", view);
		ourShader.setMat("projection", proj);

		//Scaling and Positioning Terrain
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -20.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		ourShader.setMat("model", model);
		terrain.Draw(ourShader);

		//Scaling and Positioning Plane
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(sin(lastFrame / 3)*15.0f, 20.0f, cos(lastFrame / 3)*15.0f));
		model = glm::scale(model, glm::vec3(0.4f));
		//ich hätte auch lieber glm::half_pi verwendet, das will aber nicht :(
		model = glm::rotate(model, 1.5707f + lastFrame / 3, glm::vec3(0.0f, 1.0f, 0.0f));
		ourShader.setMat("model", model);
		plane.Draw(ourShader);

		camera.Position = glm::vec3(sin(lastFrame / 3) * 15.0f, 25.0f, cos(lastFrame / 3) * 15.0f);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} glfwTerminate();
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

