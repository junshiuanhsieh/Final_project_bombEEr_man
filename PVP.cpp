#include "PVP.h"
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

void PVP(){
    if(Player_number == 1) PVP1();
    else if(Player_number == 2) PVP2();
    else if(Player_number == 3) PVP3();

}

void PVP1(){
}
void PVP2(){
}
void PVP3(){
}

