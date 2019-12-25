README

Global Variable:
  SDL_Window* gWindow;
  SDL_Renderer* gRenderer;
  Texture startgame, choosemode;
  CircleButton startbomb;
  RectButton modebuttons[TOTAL_MODEBUTTONS]
  const int SCREEN_WIDTH = 1200;
  const int SCREEN_HEIGHT = 750;
  const int TOTAL_MODEBUTTONS = 2;
  Bool quit;
  int* character;

Class:
  Rectbutton
  Circlebutton
  Texture

cpp file:
  texture.cpp
  button.cpp
  PVE.cpp
  PVP.cpp
