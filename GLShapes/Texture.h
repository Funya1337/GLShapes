#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#define STBI_FAILURE_USERMSG
#include <stb/stb_image.h>

#include <glad/glad.h>

#include "shaderClass.h"

class Texture
{
public:
  GLuint ID;
  const char* type;
  std::string path;
  GLuint unit;
  Texture(const char* image, const char* texType, GLenum slot);

  void texUnit(Shader &shader, const char* uniform, GLuint unit);
  void Bind();
  void UnBind();
  void Delete();
};

#endif