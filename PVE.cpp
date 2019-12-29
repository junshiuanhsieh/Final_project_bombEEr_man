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

    SDL_Event PVE_event;
    int rate = 5;
    while(!quit) {
        while (SDL_PollEvent(&PVE_event) != 0) {
            if (PVE_event.type == SDL_QUIT) {quit = true; return;}
            else if(PVE_event.type == SDL_KEYDOWN){
                if (PVE_event.key.keysym.sym==SDLK_RIGHT) player[0].move(RIGHT, rate);
                else if (PVE_event.key.keysym.sym==SDLK_LEFT) player[0].move(LEFT, rate);
                else if (PVE_event.key.keysym.sym==SDLK_UP) player[0].move(UP, rate);
                else if (PVE_event.key.keysym.sym==SDLK_DOWN) player[0].move(DOWN, rate);
                else player[0].finish_moving();

                if(Player_number == 2){
                    if (PVE_event.key.keysym.sym==SDLK_d) player[1].move(RIGHT, rate);
                    else if (PVE_event.key.keysym.sym==SDLK_a) player[1].move(LEFT, rate);
                    else if (PVE_event.key.keysym.sym==SDLK_w) player[1].move(UP, rate);
                    else if (PVE_event.key.keysym.sym==SDLK_s) player[1].move(DOWN, rate);
                    else player[1].finish_moving();

                    if(Player_number==3){
                        if (PVE_event.key.keysym.sym==SDLK_l) player[2].move(RIGHT, rate);
                        else if (PVE_event.key.keysym.sym==SDLK_j) player[2].move(LEFT, rate);
                        else if (PVE_event.key.keysym.sym==SDLK_i) player[2].move(UP, rate);
                        else if (PVE_event.key.keysym.sym==SDLK_k) player[2].move(DOWN, rate);
                        else player[2].finish_moving();
                    }
                }
            }
            else if(PVE_event.type == SDL_KEYUP){
                for(int i = 0; i<Player_number; i++){
                    player[i].finish_moving();
                }
            }
        }



    }
}

void PVE_Show_data(){
    for(int i = 0; i<Player_number; i++){

    }
}

void PVE_map_initialize(int random_num){
    if(random_num==0){
        map[3][0].wall = map[6][0].wall = map[7][0].wall = map[8][0].wall = 1;
        map[2][1].wall = map[3][1].wall = map[3][1].wall = map[6][1].wall = map[7][1].wall = map[8][1].wall = map[10][1].wall = map[11][1].wall = map[12][1].wall = 1;
        map[1][4].wall = map[4][4].wall = map[5][4].wall = map[6][4].wall = map[9][4].wall = map[10][4].wall = map[11][4].wall = 1;
        map[1][5].wall = map[4][5].wall = map[5][5].wall = map[6][5].wall = map[9][5].wall = map[10][5].wall = map[11][5].wall = 1;
        map[0][6].wall = map[9][6].wall = map[11][6].wall = 1;
        map[0][8].wall = 1;
        map[0][9].wall = map[1][9].wall = map[4][9].wall = map[7][9].wall = map[8][9].wall = map[12][9].wall = 1;
        map[4][10].wall = map[7][10].wall = map[8][10].wall = map[12][10].wall = 1;


        Texture PVE_background0;
        PVE_background0.loadFromFile("../PVP_image/background0.png");
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        PVE_background0.render(NULL);
        SDL_RenderPresent( gRenderer );
    }
    else if(random_num==1){
        map[3][0].wall = map[6][0].wall = map[7][0].wall = map[8][0].wall = 1;
        map[2][1].wall = map[3][1].wall = map[3][1].wall = map[6][1].wall = map[7][1].wall = map[8][1].wall = map[10][1].wall = map[11][1].wall = map[12][1].wall = 1;
        map[1][4].wall = map[4][4].wall = map[5][4].wall = map[6][4].wall = map[9][4].wall = map[10][4].wall = map[11][4].wall = 1;
        map[1][5].wall = map[4][5].wall = map[5][5].wall = map[6][5].wall = map[9][5].wall = map[10][5].wall = map[11][5].wall = 1;
        map[0][6].wall = map[9][6].wall = map[11][6].wall = 1;
        map[0][8].wall = 1;
        map[0][9].wall = map[1][9].wall = map[4][9].wall = map[7][9].wall = map[8][9].wall = map[12][9].wall = 1;
        map[4][10].wall = map[7][10].wall = map[8][10].wall = map[12][10].wall = 1;


        Texture PVE_background1;
        PVE_background1.loadFromFile("../PVP_image/background0.png");
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        PVE_background1.render(NULL);
        SDL_RenderPresent( gRenderer );
    }
    else if(random_num==2){
        map[3][0].wall = map[6][0].wall = map[7][0].wall = map[8][0].wall = 1;
        map[2][1].wall = map[3][1].wall = map[3][1].wall = map[6][1].wall = map[7][1].wall = map[8][1].wall = map[10][1].wall = map[11][1].wall = map[12][1].wall = 1;
        map[1][4].wall = map[4][4].wall = map[5][4].wall = map[6][4].wall = map[9][4].wall = map[10][4].wall = map[11][4].wall = 1;
        map[1][5].wall = map[4][5].wall = map[5][5].wall = map[6][5].wall = map[9][5].wall = map[10][5].wall = map[11][5].wall = 1;
        map[0][6].wall = map[9][6].wall = map[11][6].wall = 1;
        map[0][8].wall = 1;
        map[0][9].wall = map[1][9].wall = map[4][9].wall = map[7][9].wall = map[8][9].wall = map[12][9].wall = 1;
        map[4][10].wall = map[7][10].wall = map[8][10].wall = map[12][10].wall = 1;


        Texture PVE_background2;
        PVE_background2.loadFromFile("../PVP_image/background0.png");
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        PVE_background2.render(NULL);
        SDL_RenderPresent( gRenderer );
    }
}

