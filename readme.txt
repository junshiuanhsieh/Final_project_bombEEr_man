README

Header file link:
circular including is not allowed!!!
  button.h  include  =>  texture.h
  PVE.h     include  =>  Map.h  Player.h  Item.h  Bomb.h
  PVP.h     include  =>  Map.h  Player.h  Item.h  Bomb.h
  Map.h     include
  Player.h  include  =>  Map.h  Item.h
  Bomb.h    include  =>  Map.h  Item.h  Player.h
  Item.h    include  =>  Map.h



Global Variable:
  const int SCREEN_WIDTH;
  const int SCREEN_HEIGHT;
  SDL_Window* gWindow;
  SDL_Renderer* gRenderer;
  bool quit;
  int Player_number, Mode;
  int* character_picture;
  const int Total_item;
  Map** map;

Class:
  Rectbutton
  Circlebutton
  Texture
  Map
  Character
  Bomb
  Item
  Item_n
  Location

cpp file:
  texture.cpp
  button.cpp
  PVE.cpp
  PVP.cpp
  Map.cpp
  Bomb.cpp
  Item.cpp
  Player.cpp
