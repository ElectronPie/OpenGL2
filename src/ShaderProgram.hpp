#pragma once

#include <glm/glm.hpp>

#include <filesystem>
#include <unordered_map>

/**
 * @brief A X-macro for declaring/defining functions for setting shader uniforms
 *
 */
#define UNIFORM_FUNCS                       \
    UNIFORM_FUNC_VECTOR_1(i, int)           \
    UNIFORM_FUNC_VECTOR_1(ui, unsigned int) \
    UNIFORM_FUNC_VECTOR_1(f, float)         \
    UNIFORM_FUNC_VECTOR_2(i, int)           \
    UNIFORM_FUNC_VECTOR_2(ui, unsigned int) \
    UNIFORM_FUNC_VECTOR_2(f, float)         \
    UNIFORM_FUNC_VECTOR_3(i, int)           \
    UNIFORM_FUNC_VECTOR_3(ui, unsigned int) \
    UNIFORM_FUNC_VECTOR_3(f, float)         \
    UNIFORM_FUNC_VECTOR_4(i, int)           \
    UNIFORM_FUNC_VECTOR_4(ui, unsigned int) \
    UNIFORM_FUNC_VECTOR_4(f, float)         \
    UNIFORM_FUNC_MATRIX_M_X_M(2)            \
    UNIFORM_FUNC_MATRIX_M_X_M(3)            \
    UNIFORM_FUNC_MATRIX_M_X_M(4)            \
    UNIFORM_FUNC_MATRIX_M_X_N(2, 3)         \
    UNIFORM_FUNC_MATRIX_M_X_N(2, 4)         \
    UNIFORM_FUNC_MATRIX_M_X_N(3, 2)         \
    UNIFORM_FUNC_MATRIX_M_X_N(3, 4)         \
    UNIFORM_FUNC_MATRIX_M_X_N(4, 2)         \
    UNIFORM_FUNC_MATRIX_M_X_N(4, 3)

/**
 * @brief Represents an OpenGL shader program
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
     */
    ~ShaderProgram();

    /**
     * @brief Activate the shader program
     */
    void Bind() const noexcept;
    /**
     * @brief Deactivate the shader program
     */
    void Unbind() const noexcept;

#define UNIFORM_FUNC_VECTOR_1(PREFIX, TYPE) void SetUniform1(const std::string& name, TYPE value);

#define UNIFORM_FUNC_VECTOR_2(PREFIX, TYPE) void SetUniform2(const std::string& name, glm::vec<2, TYPE> value);

#define UNIFORM_FUNC_VECTOR_3(PREFIX, TYPE) void SetUniform3(const std::string& name, glm::vec<3, TYPE> value);

#define UNIFORM_FUNC_VECTOR_4(PREFIX, TYPE) void SetUniform4(const std::string& name, glm::vec<4, TYPE> value);

#define UNIFORM_FUNC_MATRIX_M_X_M(M) void SetUniformMat##M(const std::string& name, const glm::mat##M& matrix);

#define UNIFORM_FUNC_MATRIX_M_X_N(M, N) \
    void SetUniformMat##M##x##N(const std::string& name, const glm::mat##M##x##N& matrix);

    UNIFORM_FUNCS

#undef UNIFORM_FUNC_VECTOR_1
#undef UNIFORM_FUNC_VECTOR_2
#undef UNIFORM_FUNC_VECTOR_3
#undef UNIFORM_FUNC_VECTOR_4
#undef UNIFORM_FUNC_MATRIX_M_X_M
#undef UNIFORM_FUNC_MATRIX_M_X_N

    /**
     * @brief Checks if the shader is valid/optimal in the current OpenGL state
     * and if not, prints out exactly how
     */
    void Validate() const noexcept;

private:
    /**
     * @brief Get the OpenGL location of this shader program's uniform by name
     *
     * @param name
     * @return unsigned int
     */
    unsigned int GetUniformLocation(const std::string& name) const;

private:
    /**
     * @brief OpenGL program ID
     */
    unsigned int m_rendererID = 0;
    /**
     * @brief Stores a cache of known uniform locations by name
     */
    mutable std::unordered_map<std::string, int> m_uniformLocationCache;
};
