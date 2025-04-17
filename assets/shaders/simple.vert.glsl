#ifdef CPP_GLSL_INCLUDE
std::string simple_shader_vert_src = R"(
#version 330 core

layout(location = 0) in vec3 aPos;

void main() { gl_Position = vec4(aPos, 1.0); }
)";
#endif
