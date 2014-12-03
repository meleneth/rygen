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

    Shader* get_shader(ShaderType type, std::string raw_string);
    ShaderProgram* get_shader_program(Shader* vertex_shader, Shader* fragment_shader);

    int width;
    int height;
    SDL_Window *window;

    GLuint texid;

    GLuint entity_vbo;
    ShaderProgram *entity_shader;

    glm::mat4 View;
    glm::mat4 Projection;

    GLuint widget_vbo;
    ShaderProgram *widget_shader;

    GLuint texture_vbo;
    ShaderProgram *texture_shader;

    GLuint widget_partial_texture_vbo;
    // uses texture_shader since the shader is the same

    //WidgetRendererTileCache *tile_cache;
    
    //Font *console_font;
};

}

#endif
