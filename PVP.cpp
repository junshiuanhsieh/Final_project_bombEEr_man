#include "PVP.h"
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern bool quit;
extern int Player_number;

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

