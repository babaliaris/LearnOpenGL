#version 330 core

in vec2 textCoord;

uniform sampler2D diffuse;
uniform sampler2D specular;

out vec4 fragColor;

void main()
{
	fragColor	   = vec4(0.04, 0.28, 0.26, 1.0) + texture(diffuse, textCoord) * 0 + texture(specular, textCoord) * 0;
}