#version 430 core

out vec4 FragColor;

struct PointLight
{
    vec3 position;
    float attConst;
    float attLinear;
    float attQuadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform PointLight u_pointLight;

void main()
{
    vec3 color = (u_pointLight.ambient + u_pointLight.diffuse + u_pointLight.specular) / 3.0;
    FragColor  = vec4(color, 1.0);
}
