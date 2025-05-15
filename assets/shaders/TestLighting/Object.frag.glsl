#version 430 core

out vec4 FragColor;

uniform vec3 u_objectColor;
uniform vec3 u_lightColor;

void main()
{
    FragColor = vec4(u_objectColor * u_lightColor, 1.0);
}
