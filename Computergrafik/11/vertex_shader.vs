#version 430 core
layout (location = 0) in vec3 aPos;

layout(std430, binding = 1) buffer Value{
	float values[];
};

uniform int stepNr;

void main() {
	gl_Position = vec4(values[3*stepNr+gl_VertexID], values[3*stepNr+gl_VertexID], values[3*stepNr+gl_VertexID], 1.0);
}
