#version 330 core
out vec4 FragColor;
// used for moving the circle
uniform int offset_X;
uniform int offset_Y;

void main()
{
	FragColor = vec4(0.2f, 0.2f, 0.99f, 1.0f);
}
