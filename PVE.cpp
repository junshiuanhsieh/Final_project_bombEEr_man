#include "PVE.h"
#include <cstdlib>
#include <ctime>

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
    int map_random;
    srand(time(0));
    map_random = rand()%3;
    PVE_map_initialize(map_random);
    
}

void PVE_Show_data(){
    for(int i = 0; i<Player_number; i++){

    }
}

void PVE_map_initialize(int random_num){
    if(random_num==0){
        map[5][5].wall = 1;
        map[3][10].wall = 1;
    }
    else if(random_num==1){
        map[1][2].wall = 1;
        map[13][5].wall = 1;
    }
    else if(random_num==2){
        map[8][2].wall = 1;
        map[15][7].wall = 1;
    }
}


