#ifndef IMAGE_HPP
#define IMAGE_HPP 1

#include <string>

#include "rygen_types.hpp"
#include "mel_opengl.hpp"

namespace Rygen {
class Image {
public:
  Image();
  ~Image();
  bool load(std::string path);
  int bytes_per_pixel(void) const;
  GLenum texture_format(void) const;
  Uint16 width(void) const;
  Uint16 height(void) const;
  void *pixels(void) const;
  size_t size_in_bytes(void);

  SDL_Surface *surface; // This surface will tell us the details of the image
};
}

#endif
