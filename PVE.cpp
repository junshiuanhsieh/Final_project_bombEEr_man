#include "PVE.h"
#include "Map.h"
#include "Player.h"
#include "Bomb.h"

extern const int SCREEN_WIDTH = 1200;
extern const int SCREEN_HEIGHT = 750;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern bool quit;
extern int Player_number, Mode;
extern int* character_picture;

void PVE(){
    if(Player_number == 1) PVE1();
    else if(Player_number == 2) PVE2();
    else if(Player_number == 3) PVE3();
}

void PVE1(){
}
void PVE2(){
}
void PVE3(){
}


