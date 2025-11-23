#version 430 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_color;
layout(location = 2) in vec2 a_texCoords;

out vec3 ourColor;
out vec2 texCoords;

void main()
{
    gl_Position = vec4(a_pos, 1.0);
    ourColor    = a_color;
    texCoords   = a_texCoords;
}
