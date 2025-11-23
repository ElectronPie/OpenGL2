#version 430 core

in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D u_texture;

void main()
{
    FragColor     = texture(u_texture, texCoords);
    float average = (FragColor.r + FragColor.g + FragColor.b) / 3.0;
    FragColor     = vec4(average, average, average, 1.0);
}
