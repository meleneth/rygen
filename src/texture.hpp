#ifndef TEXTURE_INC
#define TEXTURE_INC 1

#include <string>

#include "mel_opengl.hpp"

namespace Rygen {
class Texture {
public:
  Texture();
  virtual ~Texture();

  virtual bool load(std::string path);
  size_t size_in_bytes(void) const;

  GLuint GLtexID;
  int width;
  int height;
  std::string name;
};
}

#endif
