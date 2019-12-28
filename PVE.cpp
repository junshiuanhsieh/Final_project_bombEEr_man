#include "PVE.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Renderer* gRenderer;
extern bool quit;
extern int Player_number;
extern const int Total_item;
Player* PVEplayer;
extern Map** map;

void PVE(){
    PVEplayer = new Player[Player_number];
    for(int i = 0; i<Player_number; i++) PVEplayer[i] = Player(i);
    map = new Map*[16];
    for(int i = 0; i<16; i++) map[i] = new Map [11];
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
void PVE_Show_data(){
    for(int i = 0; i<Player_number; i++){

    }
}


