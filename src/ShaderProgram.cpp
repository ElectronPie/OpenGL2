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
    unsigned int shaderRendererID = glCreateShader(type);

    const char* source_c_str = source.c_str();
    int source_length        = source.length();
    glShaderSource(shaderRendererID, 1, &source_c_str, &source_length);

    glCompileShader(shaderRendererID);

    int success;
    glGetShaderiv(shaderRendererID, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE)
    {
        int logLength;
        glGetShaderiv(shaderRendererID, GL_INFO_LOG_LENGTH, &logLength);
        char* log = (char*)alloca(logLength * sizeof(char));
        glGetShaderInfoLog(shaderRendererID, logLength, &logLength, log);
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

    m_rendererID = glCreateProgram();
    glAttachShader(m_rendererID, vertexShader);
    glAttachShader(m_rendererID, fragmentShader);
    glLinkProgram(m_rendererID);
    int success;
    glGetProgramiv(m_rendererID, GL_LINK_STATUS, &success);
    if(success == GL_FALSE)
    {
        int logLength;
        glGetProgramiv(m_rendererID, GL_INFO_LOG_LENGTH, &logLength);
        char* log = (char*)alloca(logLength * sizeof(char));
        glGetProgramInfoLog(m_rendererID, logLength, &logLength, log);
        std::cout << "Failed to link shader program:\n" << log << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_rendererID);
}

void ShaderProgram::Bind() const noexcept
{
    glUseProgram(m_rendererID);
}

void ShaderProgram::Unbind() const noexcept
{
    glUseProgram(0);
}
