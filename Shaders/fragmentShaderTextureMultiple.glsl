#version 330 core

in vec4 ex_worldPosition;
in vec4 ex_worldNormal;

out vec4 out_Color;

in vec2 uvc;

uniform vec3 cameraPosition;
uniform sampler2D textureUnitID;

#define NUM_LIGHTS 10
#define POINT_LIGHT 1U
#define DIRECTIONAL_LIGHT 2U
#define REFLECTOR_LIGHT 3U

struct Light {
    vec3 position;
    vec3 color;
    vec3 direction;

    float cutOff;
    float outerCutOff;

    unsigned int type;
};

const float constant = 1.0;
const float linear = 0.09;
const float quadratic = 0.032;

const float constantSpotLight = 1.0f;
const float linearSpotLight = 0.022f;
const float quadraticSpotLight = 0.0019f;

uniform Light lights[NUM_LIGHTS];

void main(void) {
    vec3 normal = normalize(ex_worldNormal.xyz);
    vec3 viewDir = normalize(cameraPosition - ex_worldPosition.xyz);

    vec4 result = vec4(0.0);

    for (int i = 0; i < NUM_LIGHTS; ++i) {

        if (lights[i].type == 0U) {
            continue;
        }

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

            //out_Color = vec4(0.0, 1.0, 0.0, 1.0);

            //return;
		} else if (lights[i].type == REFLECTOR_LIGHT) {
            float ambientStrength = 0.1;
            vec4 ambient = ambientStrength * vec4(lights[i].color, 1.0);

            vec3 lightVector = normalize(lights[i].position - ex_worldPosition.xyz);
            float distance = length(lights[i].position - ex_worldPosition.xyz);

            float theta = dot(lightVector, normalize(-lights[i].direction));
            float epsilon = lights[i].cutOff - lights[i].outerCutOff;
            float intensity = clamp((theta - lights[i].outerCutOff) / epsilon, 0.0, 1.0);

            float attenuation = 1.0 / (constantSpotLight + linearSpotLight * distance + quadraticSpotLight * distance * distance);

            float diff = max(dot(normal, lightVector), 0.0);
            vec4 diffuse = vec4(diff * lights[i].color, 1.0) * intensity;

            float spec = 0.0;
            vec3 reflectDir = reflect(-lightVector, normal);
            spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);

            vec4 specular = vec4(spec * lights[i].color, 1.0) * intensity;

            result += (ambient + diffuse + specular) * attenuation;
        }
    }

    vec4 textureColor = texture(textureUnitID, uvc);

    out_Color = result * textureColor;
}
