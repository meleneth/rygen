#include "demo.hpp"
#include "video.hpp"

#include "shader.hpp"
#include "shader_program.hpp"
#include "texture.hpp"

using namespace Rygen;
using namespace std;

Demo::Demo(const Video &video) {
  Projection = glm::ortho(0.0f, (float)video.width, 0.0f, (float)video.height,
                          -5.0f, 5.0f);
  View = glm::mat4(1.0f);

  glGenBuffers(1, &texture_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);

  // don't forget to flip your y axis on your UV coords
  static const GLfloat widget_texture_vbo_data[16] = {
      0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f};

  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16, widget_texture_vbo_data,
               GL_DYNAMIC_DRAW);

  auto vertex_shader = video.get_shader(VERTEX, "texture.vert");
  auto fragment_shader = video.get_shader(FRAGMENT, "texture.frag");
  texture_shader = video.get_shader_program(*vertex_shader, *fragment_shader);

  // start entity setup
  // vbo to store our vertex data on the video card
  glGenBuffers(1, &entity_vbo); // create our vbo
  glBindBuffer(GL_ARRAY_BUFFER, entity_vbo);

  // entities draw 'double sized', i.e. size is a radius
  // don't forget to flip your y axis on your UV coords
  static const GLfloat entity_vbo_data[16] = {
      -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
      1.0f,  -1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 0.0f};

  // load the vertex data into the vertex buffer object on the video card
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16, entity_vbo_data,
               GL_DYNAMIC_DRAW);

  // load_console_font();

  texture = make_shared<Texture>();
  texture->load("ship.png");

  // end widget setup
}

void Demo::render_frame(Video & video) {
  glEnable( GL_BLEND );
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
  glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);

  texture_shader->activate();

  GLuint MatrixID =
      glGetUniformLocation(texture_shader->shader_program_id, "MVP");
  GLuint TextureID =
      glGetUniformLocation(texture_shader->shader_program_id, "mytexture");

  // vertex pointer
  glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat),
                        (const GLvoid *)0);
  glEnableVertexAttribArray(0);

  // UV pointer
  glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat),
                        (const GLvoid *)8);
  glEnableVertexAttribArray(1);

  auto x = float{50.0f};
  auto y = float{50.0f};

  float width = float{128.0f};
  float height = float{128.0f};

  glm::mat4 location_matrix =
      glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.f));
  glm::mat4 scale_matrix =
      glm::scale(glm::mat4(1.0f), glm::vec3(width, height, 0.0f));

  // "Believe that I believe in you"
  glm::mat4 MVP = Projection * View * (location_matrix * scale_matrix);
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));

  glActiveTexture(GL_TEXTURE0);
  // bind the texture id as the current texture
  glBindTexture(GL_TEXTURE_2D, texture->GLtexID);
  // tell the shader to use texture 0 (TEXTURE0)
  glUniform1i(TextureID, 0);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);

  texture_shader->deactivate();

  SDL_GL_SwapWindow(video.window);  // Swap the window/buffer to display the result.
  glDisable( GL_BLEND );
}
