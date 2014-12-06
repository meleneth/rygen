#ifndef DEMO_HPP
#define DEMO_HPP


#include "mel_opengl.hpp"

#include "rygen_types.hpp"

namespace Rygen {

class Demo {
  public:
    Demo(Video& video);
    ~Demo();

    void render_frame();

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

    Texture *texture;
};

}

#endif
