cmake_minimum_required(VERSION 3.15..3.31)

set(IMGUI_USE_CXX_STDLIB ON CACHE BOOL "Allow use of C++ STL types in Dear ImGui")
set(IMGUI_USE_FONTS ON CACHE BOOL "Access additional fonts provided in Dear ImGui")
set(IMGUI_USE_FREETYPE ON CACHE BOOL "Allow use freetype fonts in Dear ImGui")
set(IMGUI_USE_SINGLE_FILE ON CACHE BOOL "Allow use of a single header file for including all of Dear ImGui")

set(IMGUI_IMPL_ALLEGRO5 OFF CACHE BOOL "Use Allegro 5 as a backend for Dear ImGui")
set(IMGUI_IMPL_ANDROID OFF CACHE BOOL "Use Android as a backend for Dear ImGui")
set(ImGUI_IMPL_DX9 OFF CACHE BOOL "Use DirectX 9 as a backend for Dear ImGui")
set(IMGUI_IMPL_DX10 OFF CACHE BOOL "Use DirectX 10 as a backend for Dear ImGui")
set(IMGUI_IMPL_DX11 OFF CACHE BOOL "Use DirectX 11 as a backend for Dear ImGui")
set(IMGUI_IMPL_DX12 OFF CACHE BOOL "Use DirectX 12 as a backend for Dear ImGui")
set(IMGUI_IMPL_GLFW OFF CACHE BOOL "Use GLFW as a backend for Dear ImGui")
set(IMGUI_IMPL_GLUT OFF CACHE BOOL "Use GLUT as a backend for Dear ImGui")
set(IMGUI_IMPL_METAL OFF CACHE BOOL "Use Metal as a backend for Dear ImGui")
set(IMGUI_IMPL_OPENGL2 OFF CACHE BOOL "Use OpenGL 2 as a backend for Dear ImGui")
set(IMGUI_IMPL_OPENGL3 OFF CACHE BOOL "Use OpenGL 3 as a backend for Dear ImGui")
set(IMGUI_IMPL_OSX OFF CACHE BOOL "Use OS X as a backend for Dear ImGui")
set(IMGUI_IMPL_SDL2 OFF CACHE BOOL "Use SDL2 as a backend for Dear ImGui")
set(IMGUI_IMPL_SDLRENDERER2 OFF CACHE BOOL "Use SDL2 renderer as a backend for Dear ImGui")
set(IMGUI_IMPL_SDL3 OFF CACHE BOOL "Use SDL3 as a backend for Dear ImGui")
set(IMGUI_IMPL_SDLRENDERER3 OFF CACHE BOOL "Use SDL3 renderer as a backend for Dear ImGui")
set(IMGUI_IMPL_SDLGPU3 OFF CACHE BOOL "Use SDLGPU3 as a backend for Dear ImGui")
set(IMGUI_IMPL_VULKAN OFF CACHE BOOL "Use Vulkan as a backend for Dear ImGui")
set(IMGUI_IMPL_WGPU OFF CACHE BOOL "Use WGPU as a backend for Dear ImGui")
set(IMGUI_IMPL_WIN32 OFF CACHE BOOL "Use Win32 as a backend for Dear ImGui")

set(IMGUI_LANGUAGES CXX)
if(IMGUI_IMPL_METAL OR IMGUI_IMPL_OSX)
    list(APPEND IMGUI_LANGUAGES OBJ_CXX)
endif()

project(imgui
    DESCRIPTION "Dear ImGui"
    LANGUAGES ${IMGUI_LANGUAGES}
)

add_library(imgui STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imconfig.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_internal.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imstb_rectpack.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imstb_textedit.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imstb_truetype.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp"
)
target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/imgui")

if(IMGUI_USE_CXX_STDLIB)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/cpp/imgui_stdlib.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/cpp/imgui_stdlib.cpp"
    )
    target_include_directories(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/cpp"
    )
endif()
if(IMGUI_USE_FONTS)
    add_executable(binary_to_compressed_c
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/fonts/binary_to_compressed_c.cpp"
    )
endif()
if(IMGUI_USE_FREETYPE)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/freetype/imgui_freetype.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/freetype/imgui_freetype.cpp"
    )
    target_include_directories(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/freetype"
    )
endif()
if(IMGUI_USE_SINGLE_FILE)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/single_file/imgui_single_file.h"
    )
    target_include_directories(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/single_file"
    )
endif()

if(IMGUI_IMPL_ALLEGRO5)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_allegro5.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_allegro5.h"
    )
endif()
if(IMGUI_IMPL_ANDROID)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_android.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_android.h"
    )
endif()
if(IMGUI_IMPL_DX9)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_dx9.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_dx9.h"
    )
endif()
if(IMGUI_IMPL_DX10)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_dx10.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_dx10.h"
    )
endif()
if(IMGUI_IMPL_DX11)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_dx11.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_dx11.h"
    )
endif()
if(IMGUI_IMPL_DX12)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_dx12.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_dx12.h"
    )
endif()
if(IMGUI_IMPL_GLFW)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.h"
    )
endif()
if(IMGUI_IMPL_GLUT)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glut.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glut.h"
    )
endif()
if(IMGUI_IMPL_METAL)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_metal.mm"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_metal.h"
    )
endif()
if(IMGUI_IMPL_OPENGL2)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl2.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl2.h"
    )
endif()
if(IMGUI_IMPL_OPENGL3)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3_loader.h"
    )
endif()
if(IMGUI_IMPL_OSX)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_osx.mm"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_osx.h"
    )
endif()
if(IMGUI_IMPL_SDL2)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdl2.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdl2.h"
    )
endif()
if(IMGUI_IMPL_SDLRENDERER2)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdlrenderer2.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdlrenderer2.h"
    )
endif()
if(IMGUI_IMPL_SDL3)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdl3.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdl3.h"
    )
endif()
if(IMGUI_IMPL_SDLRENDERER3)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdlrenderer3.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdlrenderer3.h"
    )
endif()
if(IMGUI_IMPL_SDLGPU3)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdlgpu3.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdlgpu3.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdlgpu3_shaders.h"
    )
endif()
if(IMGUI_IMPL_VULKAN)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_vulkan.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_vulkan.h"
    )
endif()
if(IMGUI_IMPL_WGPU)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_wgpu.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_wgpu.h"
    )
endif()
if(IMGUI_IMPL_WIN32)
    target_sources(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_win32.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_win32.h"
    )
endif()
target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends")
