#version 430 core

in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D u_texture;

void main()
{
    // Sample the texture at the given texture coordinates
    FragColor = texture(u_texture, texCoords);
}
