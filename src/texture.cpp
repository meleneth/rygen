#include "texture.hpp"
#include "asset_manager.hpp"
#include "console.hpp"
#include "platform.hpp"

using namespace std;
using namespace Rygen;

extern AssetManager* asset_manager;
struct twodeepoint {GLfloat x; GLfloat y;};

// Public data members go here.
Texture::Texture() : Asset()
{
    name = "Unset";
    type = Asset_Texture;
    height  = 0;
    width   = 0;
    GLtexID = -1;
}

Texture::~Texture()
{
    if (GLtexID) {
        glDeleteTextures(1, &GLtexID); 
    }
}

bool Texture::load(string filename)
{
  Asset::load(path);
  Image *image = asset_manager->get_image(filename);

  if (image != NULL) {
    name = filename;
    // Have OpenGL generate a texture object handle for us
    glGenTextures( 1, &GLtexID );

    // Bind the texture object
    glBindTexture( GL_TEXTURE_2D, GLtexID );

    width = image->width();
    height = image->height();
	int foo = image->texture_format();
	*console << foo << " texture format, " << pointer_to_hex(image->pixels()) << " pixel pointer" << endl;
    glTexImage2D(GL_TEXTURE_2D, 0, foo, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels());

    //glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //*console << "[Texture] Loaded (" << width << "x" << height << ") into glID " << GLtexID << " from " << filename << endl;
    asset_manager->release_asset( image );
    return true;
  } else {
    *console << "[Texture] SDL could not load " << filename << ": " << SDL_GetError() << endl;
    return false;
  }
}

size_t Texture::size_in_bytes(void)
{
    return -500000; // TODO
}
