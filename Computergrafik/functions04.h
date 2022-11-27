#ifndef FUNCTIONS03_H
#define FUNCTIONS03_H
#include <glad/glad.h>; // include glad to get all the required OpenGL headers 
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


void loadTexture(Shader ourShader) {

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	float borderColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE0);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // ansonsten ist das Bild kopf�ber
	unsigned char* data = stbi_load("texture1.png", &width, &height, &nrChannels, 0);
	
	// texture1 wurde ohne diese Zeile diagonal verzerrt in schwarz und wei� dargestellt
	// anscheinend ist die png nicht auf 4 byte aligned, gl verwendet anscheinend 4 als default
	// preiset die Quelle: https://stackoverflow.com/questions/15983607/opengl-texture-tilted
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Error: Could not load texture" << std::endl;
	}

	stbi_image_free(data);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);


}
float vertices[] = {

1.0f,  1.0f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
-1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
-1.0f,  1.0f, 0.0f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f
};

unsigned int indices[] = {
	0, 1, 3,  // first Triangle 
	1, 2, 3   // second Triangle
}; // note that we start from 0!
int bindBuffers() {
	unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	return VAO;

}
void draw(int VAO) {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

#endif