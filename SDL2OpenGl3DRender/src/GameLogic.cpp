#include "GameLogic.h"

#include "glm/glm.hpp"
#include "CubeShader.h"
#include "ViewPort.h"

void GameLogic::gameInit(){
  CubeShader::init();
}

void GameLogic::gameRun(float viewP_x){
  ViewPort ViewPort1;
  glm::mat4 viewPortData = ViewPort1.primary(viewP_x);
  CubeShader::fill(viewPortData);
}

void GameLogic::gameEnd(){
  CubeShader::clear();
}
