cmake_minimum_required(VERSION 3.15..3.31)

project(OpenGL2
    DESCRIPTION "My second attempt at creating an OpenGL rendering engine"
    LANGUAGES CXX)

add_executable(OpenGL2
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Application.cpp")
