bin_PROGRAMS = bin/rygen

ACLOCAL_AMFLAGS = -I m4

bin_rygen_SOURCES = src/rygen.cpp src/video.cpp src/video.hpp src/rygen_types.hpp src/mel_opengl.hpp src/console.cpp src/console.hpp src/shader.hpp src/shader.cpp src/shader_program.cpp src/shader_program.hpp src/shader_type.hpp src/demo.hpp src/demo.cpp src/texture.cpp src/texture.hpp src/image.hpp src/image.cpp
AM_CXXFLAGS = @SDL_CFLAGS@ @GLEW_CFLAGS@ 
LIBS = @SDL_LIBS@ @SDL2IMAGE_LIBS@ @GLEW_LIBS@ 
