#include "ModelTransform.h"

ModelTransform::ModelTransform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
  this->position = position;
  this->rotation = rotation;
  this->scale = scale;
}

void ModelTransform::setTransformParams()
{
  model = glm::mat4(1.0f);
  model = glm::translate(model, position);
  model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
  model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
  model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
  model = glm::scale(model, scale);
}

glm::vec3 ModelTransform::getPosition()
{
  return this->position;
}

glm::vec3 ModelTransform::getRotation()
{
  return this->rotation;
}

glm::vec3 ModelTransform::getScale()
{
  return this->scale;
}

glm::mat4& ModelTransform::getModel()
{
  return this->model;
}

void ModelTransform::setPosition(glm::vec3 position)
{
  this->position = position;
}

void ModelTransform::setRotation(glm::vec3 rotation)
{
  this->rotation = rotation;
}

void ModelTransform::setScale(glm::vec3 scale)
{
  this->scale = scale;
}