#include "shader.hpp"

#include <fstream>
#include <iostream>

#include <glad/gl.h>
#include <sstream>

Shader::Shader(const std::string &vert_filename, const std::string &frag_filename) {
  std::stringstream ss;
  unsigned int vert_shader, frag_shader;
  std::ifstream vert_file(vert_filename);

  if (!vert_file.is_open()) {
    std::cerr << "Failed to open: " << vert_filename << std::endl;
    return;
  }
  ss << vert_file.rdbuf();
  auto v_code = std::string(ss.str());
  auto v_code_c = v_code.c_str();
  
  vert_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert_shader, 1, &v_code_c, nullptr);
  glCompileShader(vert_shader);
  {
    int success;
    char infoLog[512];
    glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(vert_shader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                << infoLog << std::endl;
    }
  }
  ss.str("");
  std::ifstream frag_file(frag_filename);
  if (!frag_file.is_open()) {
    std::cerr << "Failed to open: " << frag_filename << std::endl;
    return;
  }
  ss << frag_file.rdbuf();
  auto f_code = std::string(ss.str());
  auto f_code_c = f_code.c_str();
  frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader, 1, &f_code_c, nullptr);
  glCompileShader(frag_shader);
  {
    int success;
    char infoLog[512];
    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(frag_shader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                << infoLog << std::endl;
    }
  }

  m_Program = glCreateProgram();
  glAttachShader(m_Program, vert_shader);
  glAttachShader(m_Program, frag_shader);
  glLinkProgram(m_Program);
  {
    int success;
    char infoLog[512];
    glGetProgramiv(m_Program, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(m_Program, 512, NULL, infoLog);
      std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n"
                << infoLog << std::endl;
    }
  }

  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);
}

void Shader::Use() const { glUseProgram(m_Program); }
