#include <iostream>
#include <SDL_image.h>

#include "image.hpp"
#include "console.hpp"

using namespace std;
using namespace Rygen;

Image::Image() { surface = NULL;}

Image::~Image() {
  if (surface) {
    SDL_FreeSurface(surface);
    surface = NULL;
  }
}

bool Image::load(string path) {
  if (path.size() > 0) {
    string full_path = "images/" + path;
    SDL_Surface *loader;
    if ((loader = IMG_Load(full_path.c_str()))) {
      console << full_path << " loaded fine.." << endl;
      SDL_PixelFormat RGBAFormat;
      RGBAFormat.palette = 0;
      // RGBAFormat.colorkey = 0; RGBAFormat.alpha = 0;
      RGBAFormat.BitsPerPixel = 32;
      RGBAFormat.BytesPerPixel = 4;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
      RGBAFormat.Rmask = 0xFF000000;
      RGBAFormat.Rshift = 0;
      RGBAFormat.Rloss = 0;
      RGBAFormat.Gmask = 0x00FF0000;
      RGBAFormat.Gshift = 8;
      RGBAFormat.Gloss = 0;
      RGBAFormat.Bmask = 0x0000FF00;
      RGBAFormat.Bshift = 16;
      RGBAFormat.Bloss = 0;
      RGBAFormat.Amask = 0x000000FF;
      RGBAFormat.Ashift = 24;
      RGBAFormat.Aloss = 0;
#else
      RGBAFormat.Rmask = 0x000000FF;
      RGBAFormat.Rshift = 24;
      RGBAFormat.Rloss = 0;
      RGBAFormat.Gmask = 0x0000FF00;
      RGBAFormat.Gshift = 16;
      RGBAFormat.Gloss = 0;
      RGBAFormat.Bmask = 0x00FF0000;
      RGBAFormat.Bshift = 8;
      RGBAFormat.Bloss = 0;
      RGBAFormat.Amask = 0xFF000000;
      RGBAFormat.Ashift = 0;
      RGBAFormat.Aloss = 0;
#endif

      if (loader == NULL) {
        console << "SDL_Image error loading " << full_path << endl;
        // handle the error somehow
      }

      surface = SDL_ConvertSurface(loader, &RGBAFormat, SDL_SWSURFACE);
      SDL_FreeSurface(loader);

      // Check that the image's width is a power of 2
      if ((surface->w & (surface->w - 1)) != 0) {
      }
      // Also check if the height is a power of 2
      if ((surface->h & (surface->h - 1)) != 0) {
      }
      return true;
    } else {
      console << full_path << " failed to load :(" << endl;
      return false;
    }
  }
  return false;
}

int Image::bytes_per_pixel() const {
  if (surface)
    return surface->format->BytesPerPixel;

  return -1;
}

GLenum Image::texture_format() const {
  if (surface) {
    if (bytes_per_pixel() == 4) {
      if (surface->format->Rmask == 0x000000ff)
        return GL_RGBA;
      else
        return GL_BGRA;
    }

    if (bytes_per_pixel() == 3) {
      console << "wtf, no alpha channel?" << endl;
      if (surface->format->Rmask == 0x000000ff)
        return GL_RGB;
      else
        return GL_BGR;
    }

    console << "warning: the image is not truecolor..  this will probably break"
            << endl;
    console << "warning: defaulting to RGB (no alpha channel)" << endl;

    return GL_RGB;
  }
  return GL_RGB; // we have to return something
}

Uint16 Image::width() const {
  if (surface) {
    return surface->w;
  }

  return -1;
}

Uint16 Image::height() const {
  if (surface) {
    return surface->h;
  }

  return -1;
}

void *Image::pixels() const {
  if (surface)
    return surface->pixels;

  return NULL;
}

size_t Image::size_in_bytes() { return (size_t)(surface->h * surface->pitch); }
