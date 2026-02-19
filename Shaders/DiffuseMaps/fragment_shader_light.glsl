#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

uniform Material material;

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;

uniform vec3 viewPos;

void main() {
	// ambient light
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	// diffuse light
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0); // 'max' is used to avoid negative values in 'diff'
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

	// specular light
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // the exponent is the shininess value of the specular component 
	vec3 specular = light.specular * spec * (vec3(1.0)- vec3(texture(material.specular, TexCoords)));

	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result, 1.0f);
}