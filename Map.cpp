#include "Map.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern bool quit;
extern int Player_number, Mode;
extern int* character_picture;
extern const int Total_item;
Map** map = NULL;

Map::Map(){
    character_inside = new bool[Player_number];
    contain_bomb = 0;
    wall = 0;
    for(int i = 0; i<Player_number; i++) {
        character_inside[i] = 0;
        contain_item[i] = 0;
        item[i] = NULL;
    }

    //more
}
void Map::collapse(){

}
void Map::met_character(int player){

}
void Map::item_taken(int player){

}

