#version 330 core

in vec3 normal;
in vec3 fragPos;

out vec4 fragColor;

uniform samplerCube u_Sampler;
uniform vec3 u_camPos;

void main()
{
	vec3 view_dir	= normalize(fragPos - u_camPos);
	vec3 reflection = normalize( reflect(view_dir, normal) );

	fragColor		= texture(u_Sampler, reflection) ;
}
