#pragma once	  // X	   Y	 Z
float vertices[] = {0.0f, 0.0f, 0.0f, //middle point
					0.0f, 1.0f, 0.0f, //top middle point
					1.0f, 0.0f, 0.0f, //middle right point
					1.0f, 1.0f, 0.0f  //upper right point
};

unsigned int indices[] = {
	0, 1, 3, // first triangle / upper left half
	0, 2, 3  // second triangle / lower right half
};

const char* vertexShaderSource = "#version 330 core\n" "layout (location = 0) in vec3 aPos;\n" "void main()\n""{\n" "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n""}\0";
const char* fragmentShaderSource = "#version 330 core\n" "out vec4 FragColor;\n" "void main()\n" "{\n""FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n""}\0";

int createShader() {
	unsigned int vertexShader, fragmentShader, shaderProgram;
	// insert code here
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
		infoLog << std::endl;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

int bindbuffers() {
	unsigned int VBO, VAO, EBO;
	// insert code here
	glGenBuffers(1, &VBO);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	return VAO;
}
void draw(int VAO, int shaderProgram) {
	// insert code here
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}


