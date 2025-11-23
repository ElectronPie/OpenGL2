#version 430 core

out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoords;

#define NR_DIFFUSE_MAPS  1
#define NR_SPECULAR_MAPS 1

//#define NR_EMISSION_MAPS 1
struct Material
{
    sampler2D diffuse[NR_DIFFUSE_MAPS];
    sampler2D specular[NR_SPECULAR_MAPS];
    //sampler2D emission[NR_EMISSION_MAPS];
    float shininess;
};

uniform Material u_material;

struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight u_dirLight;

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

#define NR_POINT_LIGHTS 4
uniform PointLight u_pointLights[NR_POINT_LIGHTS];

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // Ambient shading
    vec3 ambient  = vec3(0.0);
    for(int i = 0; i < NR_DIFFUSE_MAPS; ++i)
    {
        ambient += light.ambient * vec3(texture(u_material.diffuse[i], texCoords));
    }
    // Diffuse shading
    vec3 diffuse = vec3(0.0);
    float diff   = max(dot(normal, lightDir), 0.0);
    for(int i = 0; i < NR_DIFFUSE_MAPS; ++i)
    {
        diffuse += light.diffuse * diff * vec3(texture(u_material.diffuse[i], texCoords));
    }
    // Specular shading
    vec3 specular   = vec3(0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec      = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    for(int i = 0; i < NR_SPECULAR_MAPS; ++i)
    {
        specular += light.specular * spec * vec3(texture(u_material.specular[i], texCoords));
    }
    // Emission shading
    //vec3 emission = vec3(0.0);
    //for(int i = 0; i < NR_EMISSION_MAPS; ++i)
    //{
    //    emission += vec3(texture(u_material.emission[i], texCoords));
    //}
    // Combine results
    return ambient + diffuse + specular /* + emission */;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir     = normalize(light.position - fragPos);
    // Attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.attConst + light.attLinear * distance + light.attQuadratic * distance * distance);
    // Ambient shading
    vec3 ambient      = vec3(0.0);
    for(int i = 0; i < NR_DIFFUSE_MAPS; ++i)
    {
        ambient += light.ambient * attenuation * vec3(texture(u_material.diffuse[i], texCoords));
    }
    // Diffuse shading
    vec3 diffuse = vec3(0.0);
    float diff   = max(dot(normal, lightDir), 0.0);
    for(int i = 0; i < NR_DIFFUSE_MAPS; ++i)
    {
        diffuse += light.diffuse * attenuation * diff * vec3(texture(u_material.diffuse[i], texCoords));
    }
    // Specular shading
    vec3 specular   = vec3(0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec      = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    for(int i = 0; i < NR_SPECULAR_MAPS; ++i)
    {
        specular += light.specular * attenuation * spec * vec3(texture(u_material.specular[i], texCoords));
    }
    // Emission shading
    //vec3 emission = vec3(0.0);
    //for(int i = 0; i < NR_EMISSION_MAPS; ++i)
    //{
    //    emission += vec3(texture(u_material.emission[i], texCoords));
    //}
    // Combine results
    return ambient + diffuse + specular /* + emission */;
}

void main()
{
    // properties
    vec3 norm    = normalize(normal);
    vec3 viewDir = normalize(-fragPos);

    vec3 result = vec3(0);
    // Directional light
    result += CalcDirLight(u_dirLight, norm, viewDir);
    // Point lights
    for(uint i = 0; i < NR_POINT_LIGHTS; ++i)
    {
        result += CalcPointLight(u_pointLights[i], norm, fragPos, viewDir);
    }

    FragColor = vec4(result, 1.0);
}
