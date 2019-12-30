#include "Bomb.h"
#include "Map.h"
#include "Player.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Renderer* gRenderer;
extern int Player_number, Mode;
extern int* character_picture;
extern const int Total_item;
extern Map** map;
extern Player* player;

Bomb::Bomb(){
    bomb_distance = 1;
    clk = clock();
}
Bomb::Bomb(Location loc, int distance) : bomb_loc(loc), bomb_distance(distance){
    clk = clock();
}
Bomb::Bomb(Bomb &copy){
    bomb_loc = copy.bomb_loc;
    bomb_distance = copy.bomb_distance;
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
