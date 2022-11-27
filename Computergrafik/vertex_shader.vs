 #version 330 core
 layout (location = 0) in vec3 aPos;
 layout (location = 2) in vec2 aTexCoord;

	// insert code here
layout (location = 1) in vec3 aColor;
out vec3 col;
out vec2 TexCoord;

 void main()
 {
	// insert code here
	 gl_Position = vec4(aPos, 1.0);
	 col = aColor;
	 TexCoord = vec2(aTexCoord.x, aTexCoord.y);

 }