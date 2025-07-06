#version 430 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texCoords;

out vec3 fragPos;
out vec3 normal;
out vec2 texCoords;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;
uniform mat3 u_normal;

void main()
{
    gl_Position = u_proj * u_view * u_model * vec4(a_pos, 1.0);
    fragPos = vec3(u_view * u_model * vec4(a_pos, 1.0));
    normal = u_normal * a_normal;
    texCoords = a_texCoords;
}
