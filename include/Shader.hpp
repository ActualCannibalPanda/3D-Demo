#ifndef __HPP_EXAMPLE_SHADER__
#define __HPP_EXAMPLE_SHADER__

class Shader {
public:
  Shader(const std::string &vert_code, std::string &frag_code) {
    unsigned int vert_shader, frag_shader;
    vert_shader = glCreateShader(GL_VERTEX_SHADER);
    auto v_code = vert_code.c_str();
    glShaderSource(vert_shader, 1, &v_code, nullptr);
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

    frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    auto f_code = frag_code.c_str();
    glShaderSource(frag_shader, 1, &f_code, nullptr);
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

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
  }

  void Use() const { glUseProgram(m_Program); }

private:
  unsigned int m_Program;
};

#endif /* __HPP_EXAMPLE_SHADER__ */
