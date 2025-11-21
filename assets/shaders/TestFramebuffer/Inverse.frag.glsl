#version 430 core

in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D u_texture;

void main()
{
    FragColor = vec4(vec3(1.0 - texture(u_texture, texCoords)), 1.0);
}
