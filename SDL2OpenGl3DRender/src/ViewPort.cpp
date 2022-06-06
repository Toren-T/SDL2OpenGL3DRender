#include "ViewPort.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

glm::mat4 ViewPort::primary(float xInput){

  static float viewX = 0;
  viewX += xInput;

  glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
  // Camera matrix
  glm::mat4 view = glm::lookAt(glm::vec3(4,3,-3), //Camera is at (4,3,-3), in World Space
                               glm::vec3(0,0,0), //Looks at the origin
                               glm::vec3(0,1,0)); //Upright View
  //View port looks at point of origin
  glm::mat4 model = glm::mat4(1.0f);

  model = glm::rotate(model, glm::radians(viewX), glm::vec3(0.f, 1.f, 0.f));

  return (projection * view * model);
}
