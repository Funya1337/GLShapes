#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
  Shader(const char* vShaderPath, const char* fShaderPath);
  ~Shader();
  void use();
  unsigned int ID();
  void SetFloatVec(const std::string& name, float* vec, int vec_size) const;
  void setMatrix4f(const std::string& name, glm::mat4& m);

private:
  unsigned int programID;
  void errorHandler(unsigned int shader, std::string type);
  std::string getShaderCode(const char* shaderPath);

  // approaches
  const char* heapAllocApproach(const char* shaderPath);
  std::string noAllocApproach(const char* shaderPath);
};

