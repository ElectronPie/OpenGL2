#pragma once

#include <filesystem>

/**
 * @brief Represents an OpenGL shader program
 *
 */
class ShaderProgram
{
public:
    /**
     * @brief Construct a new Shader Program object
     *
     * @param vertexSourcePath File path to a vertex shader source file
     * @param fragmentSourcePath File path to a fragment shader source file
     */
    ShaderProgram(const std::filesystem::path& vertexSourcePath, const std::filesystem::path& fragmentSourcePath);
    /**
     * @brief Destroy the Shader Program object
     *
     */
    ~ShaderProgram();

    /**
     * @brief Activate the shader program
     *
     */
    void Bind() const noexcept;
    /**
     * @brief Deactivate the shader program
     *
     */
    void Unbind() const noexcept;

private:
    /**
     * @brief OpenGL program ID
     *
     */
    unsigned int m_rendererID = 0;
};
