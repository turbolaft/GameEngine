#version 330 core

out vec4 FragColor;

in vec2 uvc;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_specular1;

void main()
{
    // Sample the diffuse textures
    vec4 diffuse1 = texture(texture_diffuse1, uvc);
    vec4 diffuse2 = texture(texture_diffuse2, uvc);
    
    // Simple blend between two diffuse maps (50-50 blend)
    vec4 blendedDiffuse = mix(diffuse1, diffuse2, 0.5);
    
    // Specular contribution (example: using only one specular map)
    vec4 specular = texture(texture_specular1, uvc);
    
    // Final color output
    FragColor = blendedDiffuse + specular * 0.3;  // Mix in some specular
}
