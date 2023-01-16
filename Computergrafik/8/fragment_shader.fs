#version 330 core
in vec3 Normal;
in vec3 FragPos;
in vec3 LightColor;
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform int shaderType;

void main()
{
    if(shaderType == 1) {
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

        vec3 rgbVals = vec3((ambient + diffuse + specular) * objectColor);
        FragColor = vec4( rgbVals, 1.0);
    } else if(shaderType == 2) {
	    FragColor = vec4(LightColor * objectColor, 1.0);
	}
}