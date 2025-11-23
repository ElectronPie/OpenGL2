#version 430 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec2 a_texCoords;

out vec2 texCoords;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

void main()
{
    gl_Position = u_proj * u_view * u_model * vec4(a_pos, 1.0);
    texCoords   = a_texCoords;
}
