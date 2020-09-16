#version 330 core

in vec2 textCoord;

out vec4 fragColor;

uniform sampler2D u_Framebuffer;

void main()
{
	fragColor = vec4(vec3(1 - texture(u_Framebuffer, textCoord)), 1) ;
}