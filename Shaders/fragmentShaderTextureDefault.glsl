#version 330

out vec4 FragColor;
uniform sampler2D textureUnitID;
in vec2 uvc;

void main()
{
	vec2 vcc = uvc;
	vcc.y = 1.0 - vcc.y;
	
	FragColor = texture(textureUnitID, vcc);
}