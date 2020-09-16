#version 330 core


in vec3 textCoord;
out vec4 fragColor;

uniform samplerCube u_Sampler;

void main()
{
	fragColor = texture(u_Sampler, textCoord);
	//fragColor = vec4(textCoord, 1.0);
}