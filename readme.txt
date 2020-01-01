README

Header file link:
circular including is not allowed!!!
  button.h  include  =>  texture.h
  PVE.h     include  =>  Map.h  Player.h  Item.h  Bomb.h  Location.h
  PVP.h     include  =>  Map.h  Player.h  Item.h  Bomb.h  Location.h
  Map.h     include  =>  Location.h  Item.h
  Player.h  include  =>  Location.h  Item.h  Bomb.h
  Bomb.h    include  =>  Location.h
  Item.h    include  =>  Location.h



Global Variable:
  const int SCREEN_WIDTH;
  const int SCREEN_HEIGHT;
  SDL_Window* gWindow;
  SDL_Renderer* gRenderer;
  bool quit;
  int Player_number, Mode;
  int* character_picture;
  Bomb* bomb;
  int bomb_num;
  Player * player
  const int Total_item;
  Map** map;
  Texture bomb_texture, emptybox_texture, item_texture[12], itembox_texture, explode_texture, cross_texture;

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
