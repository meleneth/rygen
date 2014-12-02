#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "video.hpp"
#include "console.hpp"

using namespace Rygen;
using namespace std;

Video::Video(int width, int height)
{
  this->width = width;
  this->height = height;

  Projection = glm::ortho( 0.0f, (float)width, 0.0f, (float)height, -5.0f, 5.0f);
  View  = glm::mat4(1.0f);

  //tile_cache = new WidgetRendererTileCache();
  //console_font = NULL;

  console << "[WidgetRenderer] WidgetRenderer::WidgetRenderer() finished" << endl;
}

Video::~Video()
{
}

void Video::setup()
{
  // init random number generator
  srand((unsigned)time(0));
  console << "[WidgetRenderer] Going in hot, calling SDL_Init.." << endl;
  SDL_Init(SDL_INIT_VIDEO); // Init SDL2 (you should check for errors)

  // set all our awesome opengl parameters 
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE,     8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,   8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  24);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // turn on 4x anti-aliasing
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

  // request a 3.0 opengl context  
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

  // Create a window. Window mode MUST include SDL_WINDOW_OPENGL for use with OpenGL.
  window = SDL_CreateWindow( ".sapien.", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
  
  // Create an OpenGL context associated with the window.
  //SDL_GLContext glcontext = SDL_GL_CreateContext(window);
  SDL_GL_CreateContext(window);

  // ask glew to activate opengl extensions
  glewExperimental = GL_TRUE;
  int err = glewInit();
  if (err != GLEW_OK) {
      fprintf(stdout, "Glew error occured: %s\n", glewGetErrorString(err));
      exit(1);
  }
  
  // start entity setup
  // vbo to store our vertex data on the video card
  glGenBuffers(1, &entity_vbo);              // create our vbo
  glBindBuffer(GL_ARRAY_BUFFER, entity_vbo);

  // entities draw 'double sized', i.e. size is a radius
  // don't forget to flip your y axis on your UV coords
  static const GLfloat entity_vbo_data[16] = {
	  -1.0f, -1.0f, 0.0f,  1.0f,
	  -1.0f,  1.0f, 0.0f,  0.0f,
	   1.0f, -1.0f, 1.0f,  1.0f,
	   1.0f,  1.0f, 1.0f,  0.0f
  };

  // load the vertex data into the vertex buffer object on the video card
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16, entity_vbo_data, GL_DYNAMIC_DRAW);

  //Shader* vertex_shader   = asset_manager->get_shader(VERTEX, "entity.vert");
  //Shader* fragment_shader = asset_manager->get_shader(FRAGMENT, "entity.frag");
  //entity_shader   = asset_manager->get_shader_program(vertex_shader, fragment_shader);
  // end entity setup

  // start widget setup
  glGenBuffers(1, &widget_vbo);              // create our vbo
  glBindBuffer(GL_ARRAY_BUFFER, widget_vbo);

  // widgets draw exact size
  static const GLfloat widget_vbo_data[8] = {
    0.0f, 0.0f, 
    0.0f, 1.0f, 
    1.0f, 0.0f, 
    1.0f, 1.0f, 
  };

  // load the vertex data into the vertex buffer object on the video card
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, widget_vbo_data, GL_DYNAMIC_DRAW);

  //vertex_shader   = asset_manager->get_shader(VERTEX, "widget.vert");
  //fragment_shader = asset_manager->get_shader(FRAGMENT, "widget.frag");
  //widget_shader   = asset_manager->get_shader_program(vertex_shader, fragment_shader);

  glGenBuffers(1, &texture_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);

  // don't forget to flip your y axis on your UV coords
  static const GLfloat widget_texture_vbo_data[16] = {
	  0.0f, 0.0f, 0.0f, 1.0f,
	  0.0f, 1.0f, 0.0f, 0.0f,
	  1.0f, 0.0f, 1.0f, 1.0f,
	  1.0f, 1.0f, 1.0f, 0.0f
  };

  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16, widget_texture_vbo_data, GL_DYNAMIC_DRAW);

  //vertex_shader   = asset_manager->get_shader(VERTEX, "texture.vert");
  //fragment_shader = asset_manager->get_shader(FRAGMENT, "texture.frag");
  //texture_shader  = asset_manager->get_shader_program(vertex_shader, fragment_shader);

  //load_console_font();

  // end widget setup
}
