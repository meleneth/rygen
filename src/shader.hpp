#ifndef __SHADER_HPP
#define __SHADER_HPP 1

#include <string>

#include "mel_opengl.hpp"
#include "shader_type.hpp"

namespace Rygen {

class Shader {
public:
  Shader(ShaderType stype);
  virtual ~Shader();

  void print_log(GLuint object);
  virtual bool load(std::string path);
  size_t size_in_bytes(void);

  GLuint shader_id;
  ShaderType shader_type;
  std::string base_shader_path;
};
}

#endif
