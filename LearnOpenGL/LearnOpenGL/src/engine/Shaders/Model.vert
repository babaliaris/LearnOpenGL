#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 fragPos;
out vec3 normal;
out vec2 textCoord;

void main()
{
    
    //Send the fragment position.
    fragPos = vec3(model * vec4(aPos, 1.0));

    //Send the normal.
    normal = normalize(mat3(transpose(inverse(model))) * aNormal);

    //Pass the texture coordinates to the fragment shader.
    textCoord = aTextCoord;

    //GL Position.
    gl_Position = proj * view * model * vec4(aPos, 1.0);
}