#version 330 core

in vec4 ex_worldPosition;
in vec4 ex_worldNormal;
out vec4 out_Color;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 cameraPosition;

uniform float constant;
uniform float linear;
uniform float quadratic;

void main(void) {
    vec3 normal = normalize(ex_worldNormal.xyz);
    
    vec3 lightVector = normalize(lightPosition - ex_worldPosition.xyz);
    
    float ambientStrength = 0.1;
    vec4 ambient = ambientStrength * vec4(lightColor, 1.0);

    float diff = max(dot(normal, lightVector), 0.0);
    vec4 diffuse = diff * vec4(lightColor, 1.0)  * vec4(0.385, 0.647, 0.812, 1.0);
    //vec4 diffuse = diff * vec4(lightColor, 1.0);

    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPosition - ex_worldPosition.xyz);
    vec3 reflectDir = reflect(-lightVector, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    
    vec4 specular = specularStrength * spec * vec4(lightColor, 1.0);

    float distance = length(lightPosition - ex_worldPosition.xyz);
    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

    vec4 result = (ambient + diffuse + specular) * attenuation;
    out_Color = result;
}