#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_


class GameWindow{
public:
  static bool init();
  static void quit();

  static void update();

  static void resizeViewport();

  static int width();
  static int height();

  static bool maximized();
  static bool fullscreen();

  static void toggleFullscreen();
};

#endif
