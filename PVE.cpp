#include "PVE.h"
#include "Map.h"
#include "Character.h"
#include "Bomb.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern bool quit;
extern int Player_number;

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


