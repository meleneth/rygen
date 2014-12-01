#include "video.hpp"
#include "console.hpp"

using namespace Rygen;
using namespace std;

Video::Video(int width, int height)
{
  this->width = width;
  this->height = height;
  if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
      console << "Unable to initialize SDL: " << SDL_GetError() << endl;
      exit(1);
  }
  
  // set opengl context to opengl 3.3 and turn on double buffering
  // call these before calling SDL_Init()
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
  
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  display_window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

  if (!display_window) {
      console << "[Ogl] Error creating window: " << SDL_GetError() << std::endl;
      exit(1);
  }
  
  context = SDL_GL_CreateContext(display_window);
  if (!context) {
      console << "[Ogl] Error creating Opengl 3.3 context: " << SDL_GetError() << std::endl;
      exit(1);
  }
  
  //glewExperimental = GL_TRUE;
  int err = glewInit();
  if (err != GLEW_OK) {
      console << "[App] Glew error occured: " << glewGetErrorString(err) << std::endl;
      exit(1);
  }

  //renderer    = glGetString( GL_RENDERER );
  //vendor      = glGetString( GL_VENDOR   );
  //version     = glGetString( GL_VERSION  );
  //glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );
  int major_version_number;
  glGetIntegerv( GL_MAJOR_VERSION, &major_version_number );
  console << "[Ogl] Opengl Version: " << major_version_number;

  int minor_version_number;
  glGetIntegerv( GL_MINOR_VERSION, &minor_version_number );
  console << "." << minor_version_number << std::endl;

}

Video::~Video()
{
}
