cmake_minimum_required(VERSION 3.15..3.31)

project(OpenGL2
    DESCRIPTION "My second attempt at creating an OpenGL rendering engine"
    LANGUAGES CXX
)

include(FetchContent)

# Let's support IDEs nicely
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# GLAD
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad")
list(APPEND OpenGL2_LIBRARIES glad)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)
list(APPEND OpenGL2_LIBRARIES glfw)

# glm
FetchContent_Declare(
    glm
    GIT_REPOSITORY  https://github.com/g-truc/glm.git
    GIT_TAG         1.0.1
)
FetchContent_MakeAvailable(glm)
list(APPEND OpenGL2_LIBRARIES glm::glm)

# debugbreak
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/debugbreak")
list(APPEND OpenGL2_LIBRARIES debugbreak)

# stb_image
# stb_include
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb")
list(APPEND OpenGL2_LIBRARIES stb)

# Dear ImGui
set(IMGUI_IMPL_GLFW ON CACHE BOOL "" FORCE)
set(IMGUI_IMPL_OPENGL3 ON CACHE BOOL "" FORCE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui")
list(APPEND OpenGL2_LIBRARIES imgui)
target_link_libraries(imgui PUBLIC glfw)

# assimp
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_VIEWER OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/assimp")
list(APPEND OpenGL2_LIBRARIES assimp)

# epics
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/epics")
list(APPEND OpenGL2_LIBRARIES epics)

set(OpenGL2_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Application.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/VAO.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/VAO.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/VBO.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/VBO.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/VBO.inl"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/VBLayout.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/VBLayout.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/EBO.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/EBO.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/EBO.inl"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/ShaderProgram.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ShaderProgram.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/Texture.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Texture.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/Camera.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Camera.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/Light.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Light.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/Mesh.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Mesh.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/Model.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Model.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/FBO.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/FBO.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/RBO.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/RBO.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/Format.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/Test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/Test.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/Test.inl"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestClearColor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestClearColor.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestTexture2D.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestTexture2D.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestTransform2D.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestTransform2D.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestMVP.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestMVP.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestCamera.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestCamera.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestShader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestShader.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestLighting.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestLighting.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestModel.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestModel.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestDepth.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestDepth.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestStencil.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestStencil.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestBlending.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestBlending.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestFaceCulling.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestFaceCulling.hpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestFramebuffer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/test/TestFramebuffer.hpp"
)

set(OpenGL2_SHADER_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/Bezier.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/BlinnWyvilCosApprox.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/CircularArcThroughPoint.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/CircularEasings.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/CircularElliptical.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/CircularEllipticalBase.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/CircularFillet.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/Constants.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/Easings.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/ExponentialBase.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/ExponentialEasings.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/Identities.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/Impulses.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/Polynomial.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/PolynomialEasings.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/Pows.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/PulsesBumpsSteps.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/SinEasings.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/snippets/UnitaryRemappings.glsl"

    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestTexture2D/TestTexture2D.vert.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestTexture2D/TestTexture2D.frag.glsl"

    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestTransform2D/TestTransform2D.vert.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestTransform2D/TestTransform2D.frag.glsl"

    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestMVP/TestMVP.vert.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestMVP/TestMVP.frag.glsl"

    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestCamera/TestCamera.vert.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestCamera/TestCamera.frag.glsl"

    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestLighting/Light.vert.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestLighting/Light.frag.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestLighting/Object.vert.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestLighting/Object.frag.glsl"

    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestModel/TestModel.vert.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestModel/TestModel.frag.glsl"

    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestDepth/TestDepth.vert.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestDepth/TestDepth.frag.glsl"

    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestStencil/TestStencil.vert.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestStencil/TestStencil.frag.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestStencil/SolidColor.frag.glsl"

    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestBlending/TestBlending.vert.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestBlending/TestBlending.frag.glsl"

    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestFaceCulling/TestFaceCulling.vert.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestFaceCulling/TestFaceCulling.frag.glsl"

    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestShader/TestShader.vert.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestShader/TestShader.frag.glsl"

    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestFramebuffer/Scene.vert.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestFramebuffer/Scene.frag.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestFramebuffer/Screen.vert.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestFramebuffer/Screen.frag.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestFramebuffer/Inverse.frag.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestFramebuffer/BlackAndWhite.frag.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestFramebuffer/Grayscale.frag.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestFramebuffer/Sharpen.frag.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestFramebuffer/Blur.frag.glsl"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/TestFramebuffer/Edges.frag.glsl"
)

add_executable(OpenGL2
    ${OpenGL2_SOURCES}
)

target_include_directories(OpenGL2 PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

list(REMOVE_DUPLICATES OpenGL2_LIBRARIES)
target_link_libraries(OpenGL2 PUBLIC ${OpenGL2_LIBRARIES})

target_compile_features(OpenGL2 PUBLIC cxx_std_20)

set(ENABLE_FANCY_DEBUG_OUTPUT YES CACHE BOOL "")
target_compile_definitions(OpenGL2 PRIVATE $<$<BOOL:${ENABLE_FANCY_DEBUG_OUTPUT}>:ENABLE_FANCY_DEBUG_OUTPUT>)
target_compile_definitions(OpenGL2 PRIVATE $<$<CONFIG:Debug>:DEBUG>)

add_custom_command(TARGET OpenGL2 POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy_directory_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:OpenGL2>/assets"
)

# Additional target to perform clang-format run, requires clang-format
find_program(CLANG_FORMAT_EXE clang-format)
if(CLANG_FORMAT_EXE)
    add_custom_target(clang-format
        COMMAND
            "${CLANG_FORMAT_EXE}"
            -i
            ${OpenGL2_SOURCES}
            ${OpenGL2_SHADER_SOURCES}
        VERBATIM)
endif()
