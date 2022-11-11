#version 330 core
out vec4 FragColor;
// used for moving the circle
uniform int offset_X;
uniform int offset_Y;

void main()
{
	vec4 blue = vec4(0.2f, 0.2f, 0.7f, 1.0f);
	vec3 orange = vec3(1.0f, 0.5f, 0.2f);

	vec2 center = vec2(400,300) + vec2(offset_X, offset_Y);

	float d = length(center - gl_FragCoord.xy) - 50;
	float t = clamp(d, 0.0, 1.0);
	vec4 circle = vec4(orange, 1.0f - t);

    FragColor = mix(blue, circle, circle.a);
}
