#include <lber.h>
#include "Bomb.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Renderer* gRenderer;
extern int Player_number, Mode;
extern int* character_picture;
extern const int Total_item;
extern Map** map;

Bomb::Bomb(){

}
Bomb::Bomb(Location loc, int distance) : bomb_loc(loc), bomb_distance(distance){

}
Location Bomb::bomb_right(){

}
Location Bomb::bomb_left(){

}
Location Bomb::bomb_up(){

}
Location Bomb::bomb_down(){

}
void Bomb::bomb_explode(){

}
void Bomb::changemap(Location){

}