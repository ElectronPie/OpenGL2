#version 430 core

in vec3 ourColor;
in vec2 texCoords;

out vec4 FragColor;

uniform float u_mixCoefficient;

uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

void main()
{
    FragColor =
        mix(texture(u_texture1, texCoords), texture(u_texture2, texCoords), u_mixCoefficient) * vec4(ourColor, 1.0);
}
