#version 330 core

in vec4 ex_worldPosition;
in vec4 ex_worldNormal;

out vec4 out_Color;

uniform vec3 cameraPosition;

#define NUM_LIGHTS 4
#define POINT_LIGHT 0
#define DIRECTIONAL_LIGHT 1
#define REFLECTOR_LIGHT 2

struct Light {
    vec3 position;
    vec3 color;
    vec3 direction;

    int type;
};

const float constant = 1.0;
const float linear = 0.09;
const float quadratic = 0.032;

uniform Light lights[NUM_LIGHTS];

void main(void) {
    vec3 normal = normalize(ex_worldNormal.xyz);
    vec3 viewDir = normalize(cameraPosition - ex_worldPosition.xyz);

    vec4 result = vec4(0.0);

    for (int i = 0; i < NUM_LIGHTS; ++i) {
        if (lights[i].type == POINT_LIGHT) {
            
            vec3 lightVector = normalize(lights[i].position - ex_worldPosition.xyz);

            float distance = length(lights[i].position - ex_worldPosition.xyz);

            float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

            float ambientStrength = 0.1;
            vec4 ambient = ambientStrength * vec4(lights[i].color, 1.0);

            float diff = max(dot(normal, lightVector), 0.0);
            vec4 diffuse = diff * vec4(lights[i].color, 1.0) * vec4(0.385, 0.647, 0.812, 1.0);

            float specularStrength = 0.5;
            vec3 reflectDir = reflect(-lightVector, normal);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
            vec4 specular = specularStrength * spec * vec4(lights[i].color, 1.0);

            result += (ambient + diffuse + specular) * attenuation;

        } else if (lights[i].type == DIRECTIONAL_LIGHT) {
			vec3 lightVector = normalize(-lights[i].direction);

            // Normalizing vectors
            vec3 normal = normalize(ex_worldNormal.xyz);
            vec3 viewDir = normalize(cameraPosition - ex_worldPosition.xyz);

            // Ambient lighting
            float ambientStrength = 0.1;
            vec4 ambient = ambientStrength * vec4(lights[i].color, 1.0);

            // Diffuse lighting
            float diff = max(dot(normal, lightVector), 0.0);
            vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);
            vec4 diffuse = diff * vec4(lights[i].color, 1.0) * objectColor;

            // Specular lighting
            float specularStrength = 0.5;
            vec3 reflectDir = reflect(-lightVector, normal);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
            vec4 specular = specularStrength * spec * vec4(lights[i].color, 1.0);

            // Sum the contributions
            result += (ambient + diffuse + specular);
		} 
    }

    out_Color = result;
}
