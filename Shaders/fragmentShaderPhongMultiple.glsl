#version 330 core

in vec4 ex_worldPosition;
in vec4 ex_worldNormal;

out vec4 out_Color;

uniform vec3 cameraPosition;

#define NUM_LIGHTS 4

struct Light {
    vec3 position;
    vec3 color;

    float constant;
    float linear;
    float quadratic;
};

uniform Light lights[NUM_LIGHTS];

void main(void) {
    vec3 normal = normalize(ex_worldNormal.xyz);
    vec3 viewDir = normalize(cameraPosition - ex_worldPosition.xyz);

    vec4 result = vec4(0.0);

    for (int i = 0; i < NUM_LIGHTS; ++i) {
        vec3 lightVector = normalize(lights[i].position - ex_worldPosition.xyz);

        float distance = length(lights[i].position - ex_worldPosition.xyz);

        float attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance));

        float ambientStrength = 0.1;
        vec4 ambient = ambientStrength * vec4(lights[i].color, 1.0);

        float diff = max(dot(normal, lightVector), 0.0);
        vec4 diffuse = diff * vec4(lights[i].color, 1.0) * vec4(0.385, 0.647, 0.812, 1.0);

        float specularStrength = 0.5;
        vec3 reflectDir = reflect(-lightVector, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
        vec4 specular = specularStrength * spec * vec4(lights[i].color, 1.0);

        result += (ambient + diffuse + specular) * attenuation;
    }

    out_Color = result;
}
