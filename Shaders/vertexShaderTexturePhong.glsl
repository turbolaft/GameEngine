#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout(location = 2) in vec2 uv;

out vec4 ex_worldPosition;
out vec4 ex_worldNormal;

out vec2 uvc;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform mat3 normalMatrix; //(M-1)T

void main(void){
    gl_Position = projection * view * model * vec4(aPos,1.0f);
    ex_worldPosition = model * vec4(aPos,1.0f);
    //ex_worldNormal = normalMatrix * aNormal;
    ex_worldNormal = vec4(mat3(transpose(inverse(model))) * aNormal, 0.0f);
    uvc = uv;
}