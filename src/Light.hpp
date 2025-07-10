#pragma once

#include <glm/glm.hpp>

class DirLight
{
public:
    /**
     * @brief Construct a new Directional Light object
     *
     * @param direction Light direction
     * @param ambient Light ambient color
     * @param diffuse Light diffuse color
     * @param specular Light specular highlight color
     */
    DirLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    /**
     * @brief Destroy the Directional Light object
     */
    ~DirLight();

public:
    /**
     * @brief Light direction
     */
    glm::vec3 direction;
    /**
     * @brief Light ambient color
     */
    glm::vec3 ambient;
    /**
     * @brief Light diffuse color
     */
    glm::vec3 diffuse;
    /**
     * @brief Light specular highlight color
     */
    glm::vec3 specular;
};

class PointLight
{
public:
    /**
     * @brief Construct a new Point Light object
     *
     * @param position Light position
     * @param ambient Light ambient color
     * @param diffuse Light diffuse color
     * @param specular Light specular highlight color
     * @param attConst Light attenuation constant term
     * @param attLinear Light attenuation linear term
     * @param attQuadratic Light attenuation quadratic term
     */
    PointLight(
        glm::vec3 position,
        glm::vec3 ambient,
        glm::vec3 diffuse,
        glm::vec3 specular,
        float attConst     = 1.0f,
        float attLinear    = 0.0f,
        float attQuadratic = 0.0f
    );
    /**
     * @brief Destroy the Point Light object
     */
    ~PointLight();

public:
    /**
     * @brief Light position
     */
    glm::vec3 position;
    /**
     * @brief Light ambient color
     */
    glm::vec3 ambient;
    /**
     * @brief Light diffuse color
     */
    glm::vec3 diffuse;
    /**
     * @brief Light specular highlight color
     */
    glm::vec3 specular;

    /**
     * @param attConst Light attenuation constant term
     */
    float attConst;
    /**
     * @brief Light attenuation linear term
     */
    float attLinear;
    /**
     * @brief Light attenuation quadratic term
     */
    float attQuadratic;

    /**
     * @brief Get the light attenuation at a given distance from the point light
     *
     * @param distance Distance from the point light
     * @return float
     */
    inline float GetAttenuation(float distance)
    {
        return 1.0f / (attConst + attLinear * distance + attQuadratic * distance * distance);
    }
};

class SpotLight
{
public:
    /**
     * @brief Construct a new Spot Light object
     *
     * @param position Light position
     * @param direction Light direction
     * @param ambient Light ambient color
     * @param diffuse Light diffuse color
     * @param specular Light specular highlight color
     * @param innerCutOfCos Ratio of a spotlight's light travel distance to the radius of it's inner cone
     * @param outerCutOfCos Ratio of a spotlight's light travel distance to the radius of it's outer cone
     * @param attConst Light attenuation constant term
     * @param attLinear Light attenuation linear term
     * @param attQuadratic Light attenuation quadratic term
     */
    SpotLight(
        glm::vec3 position,
        glm::vec3 direction,
        glm::vec3 ambient,
        glm::vec3 diffuse,
        glm::vec3 specular,
        float innerCutOfCos,
        float outerCutOffCos,
        float attConst     = 1.0f,
        float attLinear    = 0.0f,
        float attQuadratic = 0.0f
    );
    /**
     * @brief Destroy the Spot Light object
     */
    ~SpotLight();

public:
    /**
     * @brief Light position
     */
    glm::vec3 position;
    /**
     * @brief Light direction
     */
    glm::vec3 direction;
    /**
     * @brief Light ambient color
     */
    glm::vec3 ambient;
    /**
     * @brief Light diffuse color
     */
    glm::vec3 diffuse;
    /**
     * @brief Light specular highlight color
     */
    glm::vec3 specular;

    /**
     * @param attConst Light attenuation constant term
     */
    float attConst;
    /**
     * @brief Light attenuation linear term
     */
    float attLinear;
    /**
     * @brief Light attenuation quadratic term
     */
    float attQuadratic;

    /**
     * @brief Get the light attenuation at a given distance from the point light
     *
     * @param distance Distance from the point light
     * @return float
     */
    inline float GetAttenuation(float distance)
    {
        return 1.0f / (attConst + attLinear * distance + attQuadratic * distance * distance);
    }

    /**
     * @brief Ratio of a spotlight's light travel distance to the radius of it's inner cone
     */
    float innerCutOffCos;
    /**
     * @brief Ratio of a spotlight's light travel distance to the radius of it's outer cone
     */
    float outerCutOffCos;
};
