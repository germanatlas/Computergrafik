#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;
out vec3 LightColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform int shaderType;

void main()
{
	if(shaderType == 1) {
		Normal = aNormal;
		FragPos = vec3(model * vec4(aPos, 1.0f));
		gl_Position = projection * view * model * vec4(aPos, 1.0);
	} else if(shaderType == 2) {
        
		Normal = aNormal;
		FragPos = vec3(model * vec4(aPos, 1.0f));
		gl_Position = projection * view * model * vec4(aPos, 1.0);

		// ambient light
        float ambientStrength = 0.25;
        vec3 ambient = ambientStrength * lightColor;

        // diffused light
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        //specular light
        float specularStrength = 0.9;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
        vec3 specular = specularStrength * spec * lightColor;

        LightColor = (ambient + diffuse + specular);
	}
}