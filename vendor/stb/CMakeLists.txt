cmake_minimum_required(VERSION 3.15..3.31)

project(stb)

add_library(stb STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/stb.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/stb_image.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/stb_include.h"
)

target_include_directories(stb PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
