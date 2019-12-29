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

empty_box::empty_box(){destroyed = 0;}
empty_box::empty_box(Location loc) : box_loc(loc){
    destroyed = 0;
}
void empty_box::box_destroyed(){
    map[box_loc.x][box_loc.y].collapse();
}
Item::Item(Location loc, int num) : item_num(num){
    box_loc = loc;
    destroyed = 0;
    taken = 0;
    owner = -1;
}
void Item::show(){
    if(!destroyed){}
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
    map[box_loc.x][box_loc.y].which_item = -1;
}
