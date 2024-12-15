#version 330 core

in vec4 ex_worldPosition;
in vec4 ex_worldNormal;

out vec4 out_Color;

uniform vec3 cameraPosition;

#define NUM_LIGHTS 10
#define POINT_LIGHT 1U
#define DIRECTIONAL_LIGHT 2U
#define REFLECTOR_LIGHT 3U

#define PHONG 0
#define LAMBERT 1
#define BLINN_PHONG 2

struct Light {
    vec3 position;
    vec3 color;
    vec3 direction;

    float cutOff;
    float outerCutOff;

    unsigned int type;
};

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

const float constant = 1.0;
const float linear = 0.045;
const float quadratic = 0.0075;

const float constantSpotLight = 1.0f;
const float linearSpotLight = 0.022f;
const float quadraticSpotLight = 0.0019f;

uniform Light lights[NUM_LIGHTS];
uniform Material material;
uniform int lightingModel;

void main(void) {
    vec3 normal = normalize(ex_worldNormal.xyz);
    vec3 viewDir = normalize(cameraPosition - ex_worldPosition.xyz);

    vec4 result = vec4(0.0);

    for (int i = 0; i < NUM_LIGHTS; ++i) {

        if (lights[i].type == 0U) {
            continue;
        }

        vec3 lightVector;
        vec4 ambient = vec4(lights[i].color * material.ambient, 1.0);
        vec4 diffuse = vec4(0.0);
        vec4 specular = vec4(0.0);

        if (lights[i].type == POINT_LIGHT) {
            lightVector = normalize(lights[i].position - ex_worldPosition.xyz);
            float distance = length(lights[i].position - ex_worldPosition.xyz);
            float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

            float diff = max(dot(normal, lightVector), 0.0);
            diffuse = vec4((diff * material.diffuse) * lights[i].color, 1.0);

            if (lightingModel == PHONG || lightingModel == BLINN_PHONG) {
                float spec = 0.0;

                if (lightingModel == PHONG) {
                    vec3 reflectDir = reflect(-lightVector, normal);
                    spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
                } else if (lightingModel == BLINN_PHONG) {
                    vec3 halfwayDir = normalize(lightVector + viewDir);
                    spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
                }

                specular = vec4((spec * material.specular) * lights[i].color, 1.0);
            }

            result += (ambient + diffuse + specular) * attenuation;

        } else if (lights[i].type == DIRECTIONAL_LIGHT) {
            lightVector = normalize(-lights[i].direction);

            float diff = max(dot(normal, lightVector), 0.0);
            diffuse = vec4((diff * material.diffuse) * lights[i].color, 1.0);

            if (lightingModel == PHONG || lightingModel == BLINN_PHONG) {
                vec3 reflectDir;
                if (lightingModel == PHONG) {
                    reflectDir = reflect(-lightVector, normal);
                } else if (lightingModel == BLINN_PHONG) {
                    vec3 halfwayDir = normalize(lightVector + viewDir);
                    reflectDir = halfwayDir;
                }

                float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
                specular = vec4((spec * material.specular) * lights[i].color, 1.0);
            }

            result += (ambient + diffuse + specular);
        } else if (lights[i].type == REFLECTOR_LIGHT) {
            lightVector = normalize(lights[i].position - ex_worldPosition.xyz);
            float distance = length(lights[i].position - ex_worldPosition.xyz);

            float theta = dot(lightVector, normalize(-lights[i].direction));
            float epsilon = lights[i].cutOff - lights[i].outerCutOff;
            float intensity = clamp((theta - lights[i].outerCutOff) / epsilon, 0.0, 1.0);

            float attenuation = 1.0 / (constantSpotLight + linearSpotLight * distance + quadraticSpotLight * distance * distance);

            float diff = max(dot(normal, lightVector), 0.0);
            diffuse = vec4((diff * material.diffuse) * lights[i].color, 1.0) * intensity;

            float spec = 0.0;
            if (lightingModel == PHONG) {
                vec3 reflectDir = reflect(-lightVector, normal);
                spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
            } else if (lightingModel == BLINN_PHONG) {
                vec3 halfwayDir = normalize(lightVector + viewDir);
                spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
            }

            specular = vec4((spec * material.specular) * lights[i].color, 1.0) * intensity;

            result += (ambient + diffuse + specular) * attenuation;
        }
    }

    out_Color = result;
}
