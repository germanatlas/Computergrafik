#version 330 core
out vec4 FragColor;

	// insert code here
in vec3 col;
in vec2 TexCoord;

uniform sampler2D tex;

void main()
{
	// insert code here
	FragColor = texture(tex, TexCoord);
}