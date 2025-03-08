cmake_minimum_required(VERSION 3.15..3.31)

project(OpenGL2
    DESCRIPTION "My second attempt at creating an OpenGL rendering engine"
    LANGUAGES CXX
)

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

set(OpenGL2_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Application.cpp"
)

add_executable(OpenGL2
    ${OpenGL2_SOURCES}
)

list(REMOVE_DUPLICATES OpenGL2_LIBRARIES)
target_link_libraries(OpenGL2 PUBLIC ${OpenGL2_LIBRARIES})

# Additional target to perform clang-format run, requires clang-format
find_program(CLANG_FORMAT_EXE clang-format)
if(CLANG_FORMAT_EXE)
    add_custom_target(clang-format
        COMMAND
            "${CLANG_FORMAT_EXE}"
            -i
            ${OpenGL2_SOURCES}
        VERBATIM)
endif()
