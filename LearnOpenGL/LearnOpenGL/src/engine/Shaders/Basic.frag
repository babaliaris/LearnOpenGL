#version 330 core

in vec2 textCoord;

uniform sampler2D diffuse;
uniform sampler2D specular;

out vec4 fragColor;

void main()
{
	fragColor	   = texture(diffuse, textCoord) + texture(specular, textCoord) * 0;
}