#include "Shader.h"

unsigned int Shader::ID()
{
  return programID;
}

Shader::~Shader()
{
  glDeleteProgram(programID);
}

void Shader::use()
{
  glUseProgram(programID);
}

void Shader::SetFloatVec(const std::string& name, float* vec, int vec_size) const
{
  switch (vec_size)
  {
  case 1: glUniform1f(glGetUniformLocation(programID, name.c_str()), vec[0]); break;
  case 2: glUniform2f(glGetUniformLocation(programID, name.c_str()), vec[0], vec[1]); break;
  case 3: glUniform3f(glGetUniformLocation(programID, name.c_str()), vec[0], vec[1], vec[2]); break;
  case 4: glUniform4f(glGetUniformLocation(programID, name.c_str()), vec[0], vec[1], vec[2], vec[3]); break;
  default:
    std::cout << "SHADER FAILURE! NO SUCH UNIFORM VECTOR SIZE!" << std::endl;
  }
}

void Shader::setMatrix4f(const std::string& name, glm::mat4& m)
{
  glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::errorHandler(unsigned int shader, std::string type)
{
  char logInfo[1024];
  int res;
  if (type == "PROGRAM")
  {
    glGetProgramiv(shader, GL_LINK_STATUS, &res);
    if (res == 0)
    {
      glGetProgramInfoLog(shader, 1000, NULL, logInfo);
      std::cout << "Shader linking error: " << logInfo << std::endl;
    }
  }
  else
  {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
    if (res == 0)
    {
      glGetShaderInfoLog(shader, 1000, NULL, logInfo);
      std::cout << "Shader compilation error : " << logInfo << std::endl;
    }
  }
}

Shader::Shader(const char* vShaderPath, const char* fShaderPath)
{

  // approach  1 (heap alloc)
  //const char* vShaderCodeHeap = heapAllocApproach(vShaderPath);
  //std::cout << vShaderCodeHeap << std::endl;
  //delete[] vShaderCodeHeap;

  // approach  2 (no heap alloc)
  std::string vTmpShaderCode = getShaderCode(vShaderPath);
  std::string fTmpShaderCode = getShaderCode(fShaderPath);
  const char* vShaderCode = vTmpShaderCode.c_str();
  const char* fShaderCode = fTmpShaderCode.c_str();

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vShaderCode, NULL);
  glCompileShader(vertexShader);
  errorHandler(vertexShader, "SHADER");

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
  glCompileShader(fragmentShader);
  errorHandler(fragmentShader, "SHADER");

  programID = glCreateProgram();
  glAttachShader(programID, vertexShader);
  glAttachShader(programID, fragmentShader);
  glLinkProgram(programID);
  errorHandler(programID, "PROGRAM");

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

std::string Shader::getShaderCode(const char* shaderPath)
{
  std::string text, line;
  std::ifstream in(shaderPath);
  while (std::getline(in, line))
  {
    text += line + "\n";
  }
  return text;
}

const char* Shader::heapAllocApproach(const char* shaderPath)
{
  std::string* text = new std::string();
  std::string line;
  std::ifstream in(shaderPath);
  while (std::getline(in, line))
  {
    *text += line + "\n";
  }
  const char* shaderCode = text->c_str();

  std::cout << shaderCode << std::endl;

  return shaderCode;
}