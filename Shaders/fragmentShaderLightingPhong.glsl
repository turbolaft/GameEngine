#version 330 core

in vec4 ex_worldPosition;
in vec4 ex_worldNormal;
out vec4 out_Color;

uniform vec3 cameraPosition;

struct Light {
	vec3 position;
	vec3 color;
};

const float constant = 1.0;
const float linear = 0.09;
const float quadratic = 0.032;

uniform Light light;

void main(void) {
    vec3 normal = normalize(ex_worldNormal.xyz);
    
    vec3 lightVector = normalize(light.position - ex_worldPosition.xyz);
    
    float ambientStrength = 0.1;
    vec4 ambient = ambientStrength * vec4(light.color, 1.0);

    float diff = max(dot(normal, lightVector), 0.0);
    vec4 diffuse = diff * vec4(light.color, 1.0)  * vec4(0.385, 0.647, 0.812, 1.0);
    //vec4 diffuse = diff * vec4(lightColor, 1.0);

    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPosition - ex_worldPosition.xyz);
    vec3 reflectDir = reflect(-lightVector, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    
    vec4 specular = specularStrength * spec * vec4(light.color, 1.0);

    float distance = length(light.position - ex_worldPosition.xyz);
    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

    vec4 result = (ambient + diffuse + specular) * attenuation;
    out_Color = result;
}