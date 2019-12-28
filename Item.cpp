#include "Item.h"
#include "Bomb.h"
#include "Map.h"
#include "Player.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern bool quit;
extern int Player_number, Mode;
extern int* character_picture;
extern const int Total_item;
extern Map** map;

Item::Item(Location loc, int num) : item_loc(loc), item_num(num){
    revealed = 0;
    taken = 0;
    owner = -1;
}
void Item::show(){
    if(!revealed){}
    else{
        if(!taken){}
    }
}
void Item::used(){
    owner = -1;
}
void Item::taken_by_player(int player_num){
    owner = player_num;
    taken = true;
    map[item_loc.x][item_loc.y].item[item_num] = 0;
}
