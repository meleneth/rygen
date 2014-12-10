#ifndef DEMO_HPP
#define DEMO_HPP

#include "mel_opengl.hpp"

#include "rygen_types.hpp"

namespace Rygen {

class Demo {
public:
  Demo(const Video &video);

  void render_frame(Video &video);

  GLuint texid;
  GLuint entity_vbo;
  std::shared_ptr<ShaderProgram> entity_shader;

  glm::mat4 View;
  glm::mat4 Projection;

  GLuint widget_vbo;
  std::shared_ptr<ShaderProgram> widget_shader;

  GLuint texture_vbo;
  std::shared_ptr<ShaderProgram> texture_shader;

  GLuint widget_partial_texture_vbo;

  std::shared_ptr<Texture> texture;
};
}

#endif
