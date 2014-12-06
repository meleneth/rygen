#ifndef __SHADERPROGRAM_HPP
#define __SHADERPROGRAM_HPP 1

#include <string>

#define GLM_FORCE_RADIANS

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"

#include "mel_opengl.hpp"

namespace Rygen {

class ShaderProgram {
public:
  ShaderProgram();
  virtual ~ShaderProgram();

  virtual bool load(std::string vertex_and_fragment_id_str);
  size_t size_in_bytes(void);

  bool link(GLuint vertex_shader_id, GLuint fragment_shader_id);
  void activate(void);
  void deactivate(void);
  void print_log(GLuint object);

  GLint get_attribute_location(std::string var_name);
  GLint get_uniform_location(std::string var_name);
  void bind_attrib_location(GLint index, std::string name);

  GLuint shader_program_id; // shader program
};
}

#endif
