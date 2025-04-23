cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(FILES
  src/main.cpp
  src/shader.cpp)

add_subdirectory(external)

project(example VERSION 0.1)

find_package(OpenGL REQUIRED)

add_executable(example ${FILES})

configure_file(include/example.hpp.in example.hpp)

target_include_directories(example
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/assets/shaders
    ${PROJECT_SOURCE_DIR}/build
    ${OPENGL_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS})

target_link_libraries(example
  PRIVATE
    OpenGL::GL
    glfw)

add_custom_command(
  TARGET example
  POST_BUILD
  COMMAND 
    ${CMAKE_COMMAND} -E copy_directory_if_different
      "${CMAKE_CURRENT_SOURCE_DIR}/assets/"
      "$<TARGET_FILE_DIR:example>/assets"
  COMMENT "Copying Assets"
)

###############################################
# Keeping this just in case
# find_package(Vulkan COMPONENTS glslc)
# find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)
# 
# function(compile_shader target)
#   cmake_parse_arguments(PARSE_ARGV 1 arg "" "ENV;FORMAT" "SOURCES")
#   foreach(source ${arg_SOURCES})
#     add_custom_command(
#       TARGET example
#       POST_BUILD
#       COMMENT "Compiling ${arg_SOURCES}"
#       COMMAND
#         ${glslc_executable}
#         -c
#         ${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/${source}
#         -o ${CMAKE_CURRENT_SOURCE_DIR}/build/${source}.${arg_FORMAT}
#         --target-env=${arg_ENV}
#         -mfmt=${arg_FORMAT}
#     )
#     # target_sources(${target} PRIVATE ${source}.${arg_FORMAT})
#   endforeach()
# endfunction()

# compile_shader(example
#   ENV opengl
#   FORMAT num
#   SOURCES
#     simple.frag
#     simple.vert)