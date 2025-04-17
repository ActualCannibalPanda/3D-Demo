cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(FILES src/main.cpp src/gl.c)

add_subdirectory(external)

project(Example VERSION 0.1)


find_package(OpenGL REQUIRED)

add_executable(Example ${FILES})

configure_file(include/Example.hpp.in Example.hpp)

target_include_directories(Example
    PUBLIC
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/assets/shaders
        ${OPENGL_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS})

target_link_libraries(Example
    PRIVATE
        OpenGL::GL
        glfw)
