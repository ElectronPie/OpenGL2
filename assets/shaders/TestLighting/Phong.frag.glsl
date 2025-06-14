#version 430 core

out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoords;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};
uniform Material u_material;

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
    vec3 ambient = u_light.ambient * vec3(texture(u_material.diffuse, texCoords));

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(u_light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_light.diffuse * vec3(texture(u_material.diffuse, texCoords));

    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular = spec * u_light.specular * vec3(texture(u_material.specular, texCoords));

    vec3 emission = vec3(texture(u_material.emission, texCoords));

    vec3 result = ambient + diffuse + specular + emission;
    FragColor = vec4(result, 1.0);
}
