#include "PVE.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Renderer* gRenderer;
extern bool quit;
extern int Player_number;
extern const int Total_item;
extern Player* player;
extern Map** map;

void PVE(){
    player = new Player[Player_number];
    for(int i = 0; i<Player_number; i++) player[i] = Player(i);
    map = new Map*[16];
    for(int i = 0; i<16; i++) {
        map[i] = new Map [11];
        for(int j = 0; j<11; j++){
            Location temp_loc(i,j);
            map[i][j] = Map(temp_loc);
        }
    }

}

void PVE_Show_data(){
    for(int i = 0; i<Player_number; i++){

    }
}


