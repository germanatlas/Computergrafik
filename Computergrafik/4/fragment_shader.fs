#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform int tex;
uniform int offset_X;
uniform float fade;

void main()
{
	if(tex == 0) {
		vec2 pos = TexCoord + vec2(offset_X, 0);
		FragColor = texture(texture1, pos);
	} else if(tex == 1) {
		FragColor = mix(vec4(1.0f, 1.0f, 1.0f, 1.0f), texture(texture2, TexCoord), fade);
	}
}