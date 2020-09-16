#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 textCoord;

uniform mat4 view;
uniform mat4 proj;

void main()
{
	textCoord = aPos;

	vec4 position	= proj * mat4(mat3(view)) * vec4(aPos, 1.0);
	gl_Position		= position.xyww;
}