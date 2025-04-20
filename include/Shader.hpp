#ifndef __HPP_EXAMPLE_SHADER__
#define __HPP_EXAMPLE_SHADER__

#include <string>

class Shader {
public:
  Shader(const std::string &vert_code, const std::string &frag_code);
  void Use() const;

private:
  unsigned int m_Program;
};

#endif /* __HPP_EXAMPLE_SHADER__ */
