#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "GameWindow.h"
#include "GameLogic.h"

void mainLoop();

bool quit = false;

int main(int argc, char* args[]){
  //Initialize GameWindow and check if running
  if(!GameWindow::init()){return 1;}
  //Initalize first shader
  //FillShader::init();
  GameLogic::gameInit();
  //Initail GameWindow update
  GameWindow::update();
  //Start main gameloop
  while(!quit){
    mainLoop();
    SDL_Delay(16);
  }

  GameLogic::gameEnd();
  //After loop quit window and cleanup
  GameWindow::quit();
  //Return with no main errors
  return 0;
}

void mainLoop(){
  SDL_Event e;

  float outData = 0.f;
  //int tabIndex = 0;
  //Input and control loop
  while(SDL_PollEvent(&e) !=0){
    if(e.type == SDL_QUIT){quit = true;}
    if(e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){GameWindow::resizeViewport();}
    if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT){outData = -1.f;}
    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT){outData = 1.f;}
    //TODO: Replace create new shader cube with move unused cube out of viewport and move desired cube to viewport
    /*if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_TAB){
      if(tabIndex >= 1){tabIndex = 0;}
      else{tabIndex++;}}*/
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  GameLogic::gameRun(outData);

  //Continue updating the screen to render game
  GameWindow::update();
}
