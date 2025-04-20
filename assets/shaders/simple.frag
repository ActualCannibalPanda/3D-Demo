#version 450 core

#pragma shader_stage(fragment)

layout(location = 0) out vec4 FragColor;

void main() { FragColor = vec4(1.0, 0.5, 0.2, 1.0); }
