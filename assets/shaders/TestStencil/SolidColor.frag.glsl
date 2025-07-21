#version 430 core

in vec2 texCoords;

out vec4 FragColor;

uniform vec3 u_color;

void main()
{
    // Set the fragment color to the uniform color
    FragColor = vec4(u_color, 1.0);
}
