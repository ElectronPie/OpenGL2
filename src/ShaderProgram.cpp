#include "ShaderProgram.hpp"

#include "Renderer.hpp"

#include <iostream>
#include <fstream>

static std::string ReadFile(const std::filesystem::path& filePath)
{
    constexpr size_t readBlockSize = 4096;

    std::ifstream fs{filePath, std::ios::in};
    if(!fs)
    {
        std::cout << "Could not open file: " << filePath << std::endl;
    }

    std::string contents{};
    std::string buffer(readBlockSize, '\0');
    while(fs.read(&buffer[0], readBlockSize))
    {
        contents.append(buffer);
    }
    contents.append(buffer);
    return contents;
}

static unsigned int CompileShader(std::string source, unsigned int type)
{
    GLCall(unsigned int shaderRendererID = glCreateShader(type));

    const char* source_c_str = source.c_str();
    int source_length        = source.length();
    GLCall(glShaderSource(shaderRendererID, 1, &source_c_str, &source_length));

    GLCall(glCompileShader(shaderRendererID));

    int success;
    GLCall(glGetShaderiv(shaderRendererID, GL_COMPILE_STATUS, &success));
    if(success == GL_FALSE)
    {
        int logLength;
        GLCall(glGetShaderiv(shaderRendererID, GL_INFO_LOG_LENGTH, &logLength));
        char* log = (char*)alloca(logLength * sizeof(char));
        GLCall(glGetShaderInfoLog(shaderRendererID, logLength, &logLength, log));
        std::cout << "Failed to compile ";
        switch(type)
        {
        case GL_VERTEX_SHADER:
            std::cout << "vertex";
            break;
        case GL_FRAGMENT_SHADER:
            std::cout << "fragment";
            break;
        }
        std::cout << " shader:\n" << log << std::endl;

        return 0;
    }

    return shaderRendererID;
}

ShaderProgram::ShaderProgram(
    const std::filesystem::path& vertexSourcePath, const std::filesystem::path& fragmentSourcePath
)
{
    unsigned int vertexShader   = CompileShader(ReadFile(vertexSourcePath), GL_VERTEX_SHADER);
    unsigned int fragmentShader = CompileShader(ReadFile(fragmentSourcePath), GL_FRAGMENT_SHADER);

    GLCall(m_rendererID = glCreateProgram());
    GLCall(glAttachShader(m_rendererID, vertexShader));
    GLCall(glAttachShader(m_rendererID, fragmentShader));
    GLCall(glLinkProgram(m_rendererID));
    int success;
    GLCall(glGetProgramiv(m_rendererID, GL_LINK_STATUS, &success));
    if(success == GL_FALSE)
    {
        int logLength;
        GLCall(glGetProgramiv(m_rendererID, GL_INFO_LOG_LENGTH, &logLength));
        char* log = (char*)alloca(logLength * sizeof(char));
        GLCall(glGetProgramInfoLog(m_rendererID, logLength, &logLength, log));
        std::cout << "Failed to link shader program:\n" << log << std::endl;
    }

    GLCall(glDeleteShader(vertexShader));
    GLCall(glDeleteShader(fragmentShader));
}

ShaderProgram::~ShaderProgram()
{
    GLCall(glDeleteProgram(m_rendererID));
}

void ShaderProgram::Bind() const noexcept
{
    GLCall(glUseProgram(m_rendererID));
}

void ShaderProgram::Unbind() const noexcept
{
    GLCall(glUseProgram(0));
}

#define UNIFORM_FUNC_VECTOR_1(PREFIX, TYPE)                                               \
    void ShaderProgram::SetUniform1(const std::string& name, TYPE value)                  \
    {                                                                                     \
        GLCall(glProgramUniform1##PREFIX(m_rendererID, GetUniformLocation(name), value)); \
    }

#define UNIFORM_FUNC_VECTOR_2(PREFIX, TYPE)                                                            \
    void ShaderProgram::SetUniform2(const std::string& name, glm::vec<2, TYPE> value)                  \
    {                                                                                                  \
        GLCall(glProgramUniform2##PREFIX(m_rendererID, GetUniformLocation(name), value[0], value[1])); \
    }

#define UNIFORM_FUNC_VECTOR_3(PREFIX, TYPE)                                                                      \
    void ShaderProgram::SetUniform3(const std::string& name, glm::vec<3, TYPE> value)                            \
    {                                                                                                            \
        GLCall(glProgramUniform3##PREFIX(m_rendererID, GetUniformLocation(name), value[0], value[1], value[2])); \
    }

#define UNIFORM_FUNC_VECTOR_4(PREFIX, TYPE)                                                                           \
    void ShaderProgram::SetUniform4(const std::string& name, glm::vec<4, TYPE> value)                                 \
    {                                                                                                                 \
        GLCall(                                                                                                       \
            glProgramUniform4##PREFIX(m_rendererID, GetUniformLocation(name), value[0], value[1], value[2], value[3]) \
        );                                                                                                            \
    }

#define UNIFORM_FUNC_MATRIX_M_X_M(M)                                                                              \
    void ShaderProgram::SetUniformMat##M(const std::string& name, const glm::mat##M& value)                       \
    {                                                                                                             \
        GLCall(glProgramUniformMatrix##M##fv(m_rendererID, GetUniformLocation(name), 1, GL_FALSE, &value[0][0])); \
    }

#define UNIFORM_FUNC_MATRIX_M_X_N(M, N)                                                                               \
    void ShaderProgram::SetUniformMat##M##x##N(const std::string& name, const glm::mat##M##x##N& value)               \
    {                                                                                                                 \
        GLCall(glProgramUniformMatrix##M##x##N##fv(m_rendererID, GetUniformLocation(name), 1, GL_FALSE, &value[0][0]) \
        );                                                                                                            \
    }

UNIFORM_FUNCS

#undef UNIFORM_FUNC_VECTOR_1
#undef UNIFORM_FUNC_VECTOR_2
#undef UNIFORM_FUNC_VECTOR_3
#undef UNIFORM_FUNC_VECTOR_4
#undef UNIFORM_FUNC_MATRIX_M_X_M
#undef UNIFORM_FUNC_MATRIX_M_X_N

void ShaderProgram::Validate() const noexcept
{
    GLCall(glValidateProgram(m_rendererID));
    int success;
    GLCall(glGetProgramiv(m_rendererID, GL_VALIDATE_STATUS, &success));
    if(success == GL_FALSE)
    {
        int logLength;
        GLCall(glGetProgramiv(m_rendererID, GL_INFO_LOG_LENGTH, &logLength));
        char* log = (char*)alloca(logLength * sizeof(char));
        GLCall(glGetProgramInfoLog(m_rendererID, logLength, &logLength, log));
        std::cout << "Failed to validate shader program:\n" << log << std::endl;
    }
}

unsigned int ShaderProgram::GetUniformLocation(const std::string& name) const
{
    int location;
    try
    {
        location = m_uniformLocationCache.at(name);
    }
    catch(const std::out_of_range& e)
    {
        GLCall(location = glGetUniformLocation(m_rendererID, name.c_str()));
        m_uniformLocationCache[name] = location;
    }
    if(location == -1)
    {
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
    }
    return location;
}
