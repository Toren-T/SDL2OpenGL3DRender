#ifndef CUBE_SHADER_H_
#define CUBE_SHADER_H_

#include "glm/glm.hpp"

class CubeShader{
public:
  static void init();
  static void fill(glm::mat4 MVP);
  static void clear();
};

#endif
