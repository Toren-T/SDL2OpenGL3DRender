#include "GameWindow.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <string>
#include <iostream>


namespace {

  //Create SDL window and OpenGL renderer
  SDL_Window *mainWindow = nullptr;
  SDL_GLContext context;

  //Temp and Initial window resolution
  int pWidth = 640;
  int pHeight = 480;
}

bool GameWindow::init(){

  //SDL Init and check
  if(SDL_Init(SDL_INIT_VIDEO) !=0){
    std::cout << "SDL failed to initialize. SDL_Error: " << SDL_GetError() << std::endl;
    return false;
  }

  //Get width and height
  int windowWidth = pWidth;
  int windowHeight = pHeight;

  //SDL flags
  Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

  //Create main window(name, xpos, ypos, width, height, flags) and check
  mainWindow = SDL_CreateWindow("#", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, flags);
  if(!mainWindow){
    std::cout << "Failed to create window." << SDL_GetError() << std::endl;
    quit();
    return false;
  }

  //SDL OpenGL precreation settings
  //Change to fix engine better once learned of most settings
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

  //Create OpenGL rendering context and check
  context = SDL_GL_CreateContext(mainWindow);
  if(!context){
    std::cout << "Unable to create OpenGL context." << SDL_GetError() << std::endl;
    quit();
    return false;
  }
  //Link Context to window
  if(SDL_GL_MakeCurrent(mainWindow, context)){
    std::cout << "Unable to set OpenGL context." << SDL_GetError() << std::endl;
    quit();
    return false;
  }

  if(glewInit() != GLEW_OK){
    std::cout << "Unable to initialize GLEW!" << std::endl;
    return false;
  }

  const char *glVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION));
  if(!glVersion || !*glVersion){
    std::cout << "Unable to query the OpenGL version! Version = " << glVersion << std::endl;
    quit();
    return false;
  }
  if(*glVersion < '3')
  {
      std::cout << "OpenGL is less than required version." << std::endl;
      quit();
      return false;
  }

  //OpenGL initial settings
  glClearColor( 0.8f, 0.8f, 0.8f, 1.f );
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //OpenGL vsync
  if(SDL_GL_SetSwapInterval(1) == -1)
    std::cout << "Vsync error." << SDL_GetError() << std::endl;

  //Initialization was successful
  return true;
}

//Clean up SDL and OpenGL
void GameWindow::quit(){

  if(context)
    SDL_GL_DeleteContext(context);

  if(mainWindow)
    SDL_DestroyWindow(mainWindow);

  SDL_Quit();
}
//Update visuals to window
void GameWindow::update(){
  SDL_GL_SwapWindow(mainWindow);
}
//resize main window
void GameWindow::resizeViewport(){
  //Check if main window
  if(!mainWindow){return;}

  //Get and set new dimensions
  int tmpW, tmpH;
  SDL_GetWindowSize(mainWindow, &tmpW, &tmpH);
  pWidth = tmpW;
  pHeight = tmpH;
}

//Get window width
int GameWindow::width(){
  return pWidth;
}
//Get window height
int GameWindow::height(){
  return pHeight;
}
//Check if window is maximized
bool GameWindow::maximized(){
  return (SDL_GetWindowFlags(mainWindow) & SDL_WINDOW_MAXIMIZED);
}
//Check if window is fullscreen
bool GameWindow::fullscreen(){
  return (SDL_GetWindowFlags(mainWindow) & SDL_WINDOW_FULLSCREEN_DESKTOP);
}
//Currently unused fullscreen toggle
void GameWindow::toggleFullscreen(){

}



