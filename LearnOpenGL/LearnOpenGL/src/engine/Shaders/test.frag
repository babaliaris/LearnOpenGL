#version 330 core

in vec2 textCoord;

uniform sampler2D diffuse;

out vec4 fragColor;

void main()
{
    fragColor = texture(diffuse, textCoord);
}