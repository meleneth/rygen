#ifndef VIDEO_HPP
#define VIDEO_HPP

#include "mel_opengl.hpp"

namespace Rygen {

class Video {
  public:
    Video(int width, int height);
    ~Video();

    int width;
    int height;
    SDL_Window* display_window;
    SDL_GLContext context;
};

}

#endif
