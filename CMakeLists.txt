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

add_executable(OpenGL2
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Application.cpp"
)

list(REMOVE_DUPLICATES OpenGL2_LIBRARIES)
target_link_libraries(OpenGL2 PUBLIC ${OpenGL2_LIBRARIES})
