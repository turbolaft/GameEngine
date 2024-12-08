#version 330

out vec4 FragColor;
uniform sampler2D textureUnitID;
in vec2 uvc;

void main()
{
	FragColor = texture(textureUnitID, uvc);
}