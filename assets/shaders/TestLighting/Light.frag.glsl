#version 430 core

out vec4 FragColor;

struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light u_light;

void main()
{
    FragColor = vec4(u_light.ambient + u_light.diffuse + u_light.specular, 1.0);
}
