#version 430 core

out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoords;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    //sampler2D emission;
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

struct SpotLight
{
    vec3 position;
    vec3 direction;

    float attConst;
    float attLinear;
    float attQuadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float innerCutOffCos;
    float outerCutOffCos;
};

uniform SpotLight u_spotLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir   = normalize(-light.direction);
    // Ambient shading
    vec3 ambient    = light.ambient * vec3(texture(u_material.diffuse, texCoords));
    // Diffuse shading
    float diff      = max(dot(normal, lightDir), 0.0);
    vec3 diffuse    = light.diffuse * diff * vec3(texture(u_material.diffuse, texCoords));
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec      = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular   = light.specular * spec * vec3(texture(u_material.specular, texCoords));
    // Emission shading
    //vec3 emission   = vec3(texture(u_material.emission, texCoords));
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
    vec3 ambient      = light.ambient * attenuation * vec3(texture(u_material.diffuse, texCoords));
    // Diffuse shading
    float diff        = max(dot(normal, lightDir), 0.0);
    vec3 diffuse      = light.diffuse * diff * attenuation * vec3(texture(u_material.diffuse, texCoords));
    // Specular shading
    vec3 reflectDir   = reflect(-lightDir, normal);
    float spec        = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular     = light.specular * spec * attenuation * vec3(texture(u_material.specular, texCoords));
    // Emission shading
    //vec3 emission     = vec3(texture(u_material.emission, texCoords));
    // Combine results
    return ambient + diffuse + specular /* + emission */;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir     = normalize(light.position - fragPos);
    // Attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.attConst + light.attLinear * distance + light.attQuadratic * distance * distance);
    // Cut-off
    float theta       = dot(lightDir, normalize(-light.direction));
    float epsilon     = light.innerCutOffCos - light.outerCutOffCos;
    float intensity   = clamp((theta - light.outerCutOffCos) / epsilon, 0.0, 1.0);
    // Ambient shading
    // Ambient unaffected by cut-off intensity so that we always have a little light
    vec3 ambient      = light.ambient * attenuation * vec3(texture(u_material.diffuse, texCoords));
    // Diffuse shading
    float diff        = max(dot(normal, lightDir), 0.0);
    vec3 diffuse      = light.diffuse * diff * attenuation * intensity * vec3(texture(u_material.diffuse, texCoords));
    // Specular shading
    vec3 reflectDir   = reflect(-lightDir, normal);
    float spec        = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular     = light.specular * spec * attenuation * intensity * vec3(texture(u_material.specular, texCoords));
    // Emission shading
    //vec3 emission     = vec3(texture(u_material.emission, texCoords));
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
    // Spot light
    result += CalcSpotLight(u_spotLight, norm, fragPos, viewDir);

    FragColor = vec4(result, 1.0);
}
