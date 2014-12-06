#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>

#include "mel_opengl.hpp"
#include "shader.hpp"
#include "console.hpp"

using namespace std;
using namespace Rygen;

Shader::Shader(ShaderType stype) {
  base_shader_path = "shaders/";
  shader_type = stype;
  shader_id = 0;
}

Shader::~Shader() {
  if (shader_id) {
    glDeleteShader(shader_id);
  }
}

void Shader::print_log(GLuint object) {
  GLint log_length = 0;

  if (glIsShader(object))
    glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
  else if (glIsProgram(object))
    glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
  else {
    console << "[Shader] Not a shader or a program" << endl;
    return;
  }

  char *log = (char *)malloc(log_length);
  if (glIsShader(object))
    glGetShaderInfoLog(object, log_length, NULL, log);

  else if (glIsProgram(object))
    glGetProgramInfoLog(object, log_length, NULL, log);

  console << "[Shader] Log: " << log << endl;
  free(log);
}

bool Shader::load(string shader_file) {
  console << "[Shader] Loading shader file: " << shader_file << std::endl;
  string shader_source = read_text_file(shader_file.c_str());

  GLuint res = glCreateShader(shader_type == VERTEX ? GL_VERTEX_SHADER
                                                    : GL_FRAGMENT_SHADER);
  const char *source = shader_source.c_str();
  int len = strlen(source);

  glShaderSource(res, 1, &source, &len);

  glCompileShader(res);
  GLint compile_ok = GL_FALSE;
  glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
  if (compile_ok == GL_FALSE) {
    console << "[Shader] Failed to compile: " << shader_source << endl;
    print_log(res);
    glDeleteShader(res);
    return false;
  }

  shader_id = res;

  return true;
}

size_t Shader::size_in_bytes(void) { return 0; }
