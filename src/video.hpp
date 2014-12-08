#ifndef VIDEO_HPP
#define VIDEO_HPP

#include "rygen_types.hpp"

#include "mel_opengl.hpp"
#include "shader_type.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Rygen {

class Video {
public:
  Video(int width, int height);
  ~Video();

  void setup();

  ShaderPtr get_shader(const ShaderType type, const std::string raw_string) const;
  ShaderProgramPtr get_shader_program(const Shader &vertex_shader,
                                    const Shader &fragment_shader) const;

  int width;
  int height;
  SDL_Window *window;

  // uses texture_shader since the shader is the same

  // WidgetRendererTileCache *tile_cache;

  // Font *console_font;
};
}

#endif
