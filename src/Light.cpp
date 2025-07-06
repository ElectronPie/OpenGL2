#include "Light.hpp"

DirLight::DirLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular):
    direction{direction}, ambient{ambient}, diffuse{diffuse}, specular{specular}
{}

DirLight::~DirLight()
{}

PointLight::PointLight(
    glm::vec3 position,
    glm::vec3 ambient,
    glm::vec3 diffuse,
    glm::vec3 specular,
    float attConst,
    float attLinear,
    float attQuaddratic
):
    position{position}, ambient{ambient}, diffuse{diffuse}, specular{specular}, attConst{attConst},
    attLinear{attLinear}, attQuadratic{attQuaddratic}
{}

PointLight::~PointLight()
{}

SpotLight::SpotLight(
    glm::vec3 position,
    glm::vec3 direction,
    glm::vec3 ambient,
    glm::vec3 diffuse,
    glm::vec3 specular,
    float innerCutOffCos,
    float outerCutOffCos,
    float attConst,
    float attLinear,
    float attQuaddratic
):
    position{position}, direction{direction}, ambient{ambient}, diffuse{diffuse}, specular{specular},
    attConst{attConst}, attLinear{attLinear}, attQuadratic{attQuaddratic}, innerCutOffCos{innerCutOffCos},
    outerCutOffCos{outerCutOffCos}
{}

SpotLight::~SpotLight()
{}
