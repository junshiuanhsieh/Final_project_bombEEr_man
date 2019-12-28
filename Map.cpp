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

Location::Location(){
    x = 0;
    y = 0;
}

Map::Map(){

}
void Map::collapse(){

}
void Map::met_character(int player){

}
void Map::item_taken(int player){

}

