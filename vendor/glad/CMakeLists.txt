cmake_minimum_required(VERSION 3.15..3.31)

project(glad C)

add_library(glad STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c")
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
