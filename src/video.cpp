#include "video.hpp"
#include "console.hpp"
#include "shader.hpp"
#include "shader_program.hpp"

using namespace Rygen;
using namespace std;

Video::Video(int width, int height)
{
  this->width = width;
  this->height = height;

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
  SDL_GLContext glcontext = SDL_GL_CreateContext(window);
  SDL_GL_CreateContext(window);

  // ask glew to activate opengl extensions
  glewExperimental = GL_TRUE;
  int err = glewInit();
  if (err != GLEW_OK) {
      fprintf(stdout, "Glew error occured: %s\n", glewGetErrorString(err));
      exit(1);
  }
}

Shader* Video::get_shader(ShaderType type, string path)
{
    auto shader = new Shader(type);
    if( shader->load(path)) {
    } else {
        delete shader;
        shader = NULL;
    }

    return shader;
}

ShaderProgram* Video::get_shader_program(Shader* vertex_shader, Shader* fragment_shader)
{
    stringstream ss;
    ss << vertex_shader->shader_id << "|" << fragment_shader->shader_id;
    string program_id = ss.str();

    auto program = new ShaderProgram();

    if( program->link(vertex_shader->shader_id, fragment_shader->shader_id)) {
    } else {
        delete program;
        program = NULL;
    }

    return program;
}
