#version 430 core

in vec3 ourColor;
in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

void main()
{
    FragColor = mix(texture(u_texture1, texCoords), texture(u_texture2, texCoords), 0.2) * vec4(ourColor, 1.0);
}
