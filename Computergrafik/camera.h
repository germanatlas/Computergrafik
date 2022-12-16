#ifndef CAMERA_H
#define CAMERA_H
#include <iostream>
#include <glad/glad.h>
#include "shader.h"

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 direction;
float fov = 90.0f; //field of view / zoom

float yaw = -90.0f; // else it's rotated wrong at the start
float pitch = 0.0f;

glm::mat4 GetViewMatrix() {
	glm::mat4 view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	return view;
}
#endif