#version 430 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;

out vec3 lightingColor;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;
uniform mat3 u_normal;

uniform vec3 u_lightColor;
uniform vec3 u_lightPos;
uniform vec3 u_viewPos;

uniform float u_ambientStrength;
uniform float u_diffuseStrength;
uniform float u_specularStrength;
uniform float u_shininess;

vec3 mat4xvec3(mat4 A, vec3 x)
{
    return vec3(A * vec4(x, 1.0));
}

void main()
{
    vec3 pos = mat4xvec3(u_model, a_pos);
    vec3 normal = u_normal * a_normal;

    gl_Position = u_proj * u_view * u_model * vec4(a_pos, 1.0);

    vec3 ambient = u_ambientStrength * u_lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(u_lightPos - pos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_diffuseStrength * diff * u_lightColor;

    vec3 viewDir = normalize(u_viewPos - pos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_shininess);
    vec3 specular = u_specularStrength * spec * u_lightColor;

    lightingColor = ambient + diffuse + specular;
}
