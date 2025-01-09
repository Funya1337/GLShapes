#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class ModelTransform
{
public:
  ModelTransform(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f),
    glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f),
    glm::vec3 scale = glm::vec3(0.25f, 0.25f, 0.25f));

  // getters and setters
  glm::vec3 getPosition();
  glm::vec3 getRotation();
  glm::vec3 getScale();
  glm::mat4& getModel();

  void setPosition(glm::vec3 position);
  void setRotation(glm::vec3 rotation);
  void setScale(glm::vec3 scale);

  void setTransformParams();

private:
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
  glm::mat4 model = glm::mat4(1.0f);
};

