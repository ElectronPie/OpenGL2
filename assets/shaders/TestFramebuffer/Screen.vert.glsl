#version 430 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_texCoords;

out vec2 texCoords;

void main()
{
    gl_Position = vec4(a_pos, 1.0);
    texCoords = a_texCoords;
}
