#ifdef CPP_GLSL_INCLUDE
std::string simple_shader_frag_src = R"(
#version 330 core

out vec4 FragColor;

void main() { FragColor = vec4(1.0, 0.5, 0.2, 1.0); }
)";
#endif
