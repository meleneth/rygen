#include <stdio.h>
#include <stdlib.h>

#include "shader_program.hpp"
#include "console.hpp"

using namespace std;
using namespace Rygen;

ShaderProgram::ShaderProgram()
{
    shader_program_id = -1;
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::print_log(GLuint object)
{
  GLint log_length = 0;

  if (glIsShader(object))
    glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
  else if (glIsProgram(object))
    glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
  else {
    console << "printlog: Not a shader or a program" << endl;
    return;
  }

  char* log = (char*)malloc(log_length);
  if (glIsShader(object))
    glGetShaderInfoLog(object, log_length, NULL, log);

  else if (glIsProgram(object))
    glGetProgramInfoLog(object, log_length, NULL, log);

  console << "Log: " << log << endl;
  free(log);
}

bool ShaderProgram::link(GLuint vertex_shader_id, GLuint fragment_shader_id)
{
  shader_program_id = glCreateProgram();

  ///////////////////////////////////////////////////////////////////////////////////////
  // this is for the maybe one day when we try to use geometry shaders                 //
  ///////////////////////////////////////////////////////////////////////////////////////
  //if (engine->has_geometry_shader_support()) {
  //  glProgramParameteriEXT(shader_program_id, GL_GEOMETRY_INPUT_TYPE_EXT, GL_TRIANGLES);
  //  glProgramParameteriEXT(shader_program_id, GL_GEOMETRY_OUTPUT_TYPE_EXT, GL_TRIANGLE_STRIP);
  //  glProgramParameteriEXT(shader_program_id, GL_GEOMETRY_VERTICES_OUT_EXT, 3);
  //}
  ///////////////////////////////////////////////////////////////////////////////////////

  //print_log(shader_program_id);
  if ( vertex_shader_id > 0 ) {
    glAttachShader( shader_program_id, vertex_shader_id );
  }

  if ( fragment_shader_id > 0 ) {
    glAttachShader( shader_program_id, fragment_shader_id );
  }

  // this is where you could run GetAttribLocation or GetUniformLocation or whaterver
  // calls or BindAttribLocation go ahead and push your program data down to the shader
  // if you run any of these commands again later then you will have to re-link the shader_program

  glLinkProgram( shader_program_id );


  GLint linked;
  glGetProgramiv( shader_program_id, GL_LINK_STATUS, &linked );

  if ( linked == GL_FALSE )
  {
    console << "Shader linking failed" << endl;
    GLchar errorLog[1024] = {0};
    glGetProgramInfoLog(shader_program_id, 1024, NULL, errorLog);
    console << "Actual Error: " << errorLog << endl;
    return false;
  }

  GLint validated;
  glValidateProgram( shader_program_id );
  glGetProgramiv( shader_program_id, GL_VALIDATE_STATUS, &validated );
  if( validated == GL_FALSE )
  {
      GLchar errorLog[1024] = {0};
      glGetProgramInfoLog(shader_program_id, 1024, NULL, errorLog);
      console << "Error validating shader: " << errorLog << endl;
      return false;
  }

  //get_active_uniform(0); // remove this to remove all the damn console crap

  return true;
}

void ShaderProgram::activate(void)
{
  glUseProgram( shader_program_id );
}

void ShaderProgram::deactivate(void)
{
  glUseProgram( 0 );
}

GLint ShaderProgram::get_attribute_location(std::string var_name) {
    GLint attribute = glGetAttribLocation(shader_program_id, var_name.c_str());
    if(attribute == -1)
        console << "Could not find attribute location for " << var_name << endl;
    return attribute;
}

GLint ShaderProgram::get_uniform_location(std::string var_name) {
    GLint uniform = glGetUniformLocation(shader_program_id, var_name.c_str());
    if(uniform == -1)
        console << "Could not find uniform location for " << var_name << endl;
    return uniform;
}

bool ShaderProgram::load(string vertex_and_fragment_id_str)
{
    //Asset::load(vertex_and_fragment_id_str);
    return true;
}

size_t ShaderProgram::size_in_bytes(void)
{
    return 0;
}

void ShaderProgram::bind_attrib_location(GLint index, std::string name)
{
    glBindAttribLocation( shader_program_id, index, name.c_str() );
}
