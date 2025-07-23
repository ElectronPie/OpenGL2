#version 430 core

in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D u_texture;

void main()
{
    // Sample the texture at the given texture coordinates
    vec4 texColor = texture(u_texture, texCoords);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
}
