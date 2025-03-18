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
