#ifndef RYGENTYPES_HPP
#define RYGENTYPES_HPP

#include <list>
#include <string>
#include <memory>

namespace Rygen {
class Video;
class Shader;
class ShaderProgram;
class Texture;
class Demo;

typedef std::list<std::string> StringList;

typedef std::shared_ptr<Shader> ShaderPtr;
typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;
};

#endif
