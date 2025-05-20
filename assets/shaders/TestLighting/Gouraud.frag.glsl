#version 430 core

in vec3 lightingColor;

out vec4 FragColor;

uniform vec3 u_objectColor;

void main()
{
    FragColor = vec4(lightingColor * u_objectColor, 1.0);
}
