#include "PVP.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern bool quit;
extern int Player_number, Mode;
extern int* character_picture;
extern const int Total_item;
extern Player* player;
extern Map** map;

void PVP(){
    player = new Player[Player_number];
    for(int i = 0; i<Player_number; i++) player[i] = Player(i);
    map = new Map*[16];
    for(int i = 0; i<16; i++) map[i] = new Map [11];



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
void PVP_Show_data(){
    for(int i = 0; i<Player_number; i++){

    }
}

