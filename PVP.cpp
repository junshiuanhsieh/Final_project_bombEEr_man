#include "PVP.h"
#include <cstdlib>
#include <ctime>

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
extern Texture bomb_texture, emptybox_texture, item_texture[12], itembox_texture;
extern int bomb_num;
Texture PVP_background;


void PVP(){
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
    PVP_map_initialize(map_random);
    PVP_initialize();

    int rate = 8;
    bomb_num = 0;
    bool keypress[12];
    Bomb * bomb = NULL;
    SDL_Event PVP_event;

    for(int i = 0; i<12; i++) keypress[i] = 0;
    while(!quit) {
        while (SDL_PollEvent(&PVP_event) != 0) {
            if (PVP_event.type == SDL_QUIT) {quit = true; return;}
            if (PVP_event.type == SDL_KEYDOWN && PVP_event.key.repeat==0) {
                switch( PVP_event.key.keysym.sym ){
                    case SDLK_UP: keypress[Key_Up] = 1; break;
                    case SDLK_DOWN: keypress[Key_Down] = 1; break;
                    case SDLK_LEFT: keypress[Key_Left] = 1; break;
                    case SDLK_RIGHT: keypress[Key_Right] = 1; break;
                    case SDLK_RETURN:
                        if(map[player[0].player_loc.x][player[0].player_loc.y].contain_bomb==0 && player[0].bomb_left>0){
                            bomb = player[0].putbomb(bomb);
                            player[0].bomb_left--;
                        }
                        break;

                    case SDLK_w: keypress[Key_w] = 1; break;
                    case SDLK_s: keypress[Key_s] = 1; break;
                    case SDLK_a: keypress[Key_a] = 1; break;
                    case SDLK_d: keypress[Key_d] = 1; break;
                    case SDLK_TAB:
                        if(map[player[1].player_loc.x][player[1].player_loc.y].contain_bomb==0 && player[1].bomb_left>0){
                            bomb = player[1].putbomb(bomb);
                            player[1].bomb_left--;
                        }
                        break;

                    case SDLK_i: keypress[Key_i] = 1; break;
                    case SDLK_k: keypress[Key_k] = 1; break;
                    case SDLK_j: keypress[Key_j] = 1; break;
                    case SDLK_l: keypress[Key_l] = 1; break;
                    case SDLK_SPACE:
                        if(Player_number == 3){
                            if(map[player[2].player_loc.x][player[2].player_loc.y].contain_bomb==0 && player[2].bomb_left>0){
                                bomb = player[2].putbomb(bomb);
                                player[2].bomb_left--;
                            }
                            break;
                        }
                }
            }
            else if (PVP_event.type == SDL_KEYUP && PVP_event.key.repeat==0) {
                switch( PVP_event.key.keysym.sym ){
                    case SDLK_UP: keypress[Key_Up] = 0; break;
                    case SDLK_DOWN: keypress[Key_Down] = 0; break;
                    case SDLK_LEFT: keypress[Key_Left] = 0; break;
                    case SDLK_RIGHT: keypress[Key_Right] = 0; break;

                    case SDLK_w: keypress[Key_w] = 0; break;
                    case SDLK_s: keypress[Key_s] = 0; break;
                    case SDLK_a: keypress[Key_a] = 0; break;
                    case SDLK_d: keypress[Key_d] = 0; break;

                    case SDLK_i: keypress[Key_i] = 0; break;
                    case SDLK_k: keypress[Key_k] = 0; break;
                    case SDLK_j: keypress[Key_j] = 0; break;
                    case SDLK_l: keypress[Key_l] = 0; break;
                }
            }
        }

        if (keypress[Key_Up]) player[0].move(UP, rate);
        else if (keypress[Key_Down]) player[0].move(DOWN, rate);
        else if (keypress[Key_Left]) player[0].move(LEFT, rate);
        else if (keypress[Key_Right]) player[0].move(RIGHT, rate);
        else player[0].finish_moving();

        if (keypress[Key_w]) player[1].move(UP, rate);
        else if (keypress[Key_s]) player[1].move(DOWN, rate);
        else if (keypress[Key_a]) player[1].move(LEFT, rate);
        else if (keypress[Key_d]) player[1].move(RIGHT, rate);
        else player[1].finish_moving();

        if(Player_number==3){
            if (keypress[Key_i]) player[2].move(UP, rate);
            else if (keypress[Key_k]) player[2].move(DOWN, rate);
            else if (keypress[Key_j]) player[2].move(LEFT, rate);
            else if (keypress[Key_l]) player[2].move(RIGHT, rate);
            else player[2].finish_moving();
        }

        for(int i = 0; i<bomb_num; i++){
            if(clock() - bomb[i].clk > 100000){
                bomb = bomb[i].bomb_explode(i, bomb);
                i--;
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        PVP_background.render(NULL);
        for(int i = 0; i<16; i++){
            for(int j = 0; j<11; j++){
                map[i][j].render_map();
            }
        }
        for(int i = 0; i<Player_number; i++) player[i].player_render();
        SDL_RenderPresent( gRenderer );
    }
}

void PVP_initialize(){
    bomb_texture.loadFromFile("../item_image/bomb.png");
    itembox_texture.loadFromFile("../item_image/box.png");
    emptybox_texture.loadFromFile("../item_image/empty_box.png");
    //item_texture.loadFromFile

    for(int i = 0; i<Player_number; i++){
        if(character_picture[i]==0) player[i].picture.loadFromFile("../character_image/character0.png");
        else if(character_picture[i]==1) player[i].picture.loadFromFile("../character_image/character1.png");
        else if(character_picture[i]==2) player[i].picture.loadFromFile("../character_image/character2.png");
        else if(character_picture[i]==3) player[i].picture.loadFromFile("../character_image/character3.png");
        else if(character_picture[i]==4) player[i].picture.loadFromFile("../character_image/character4.png");
    }
    player[0].player_loc.x = 15;
    player[0].player_loc.y = 10;
    player[0].player_point.x = 920;
    player[0].player_point.y = 675;

    player[1].player_loc.x = 0;
    player[1].player_loc.y = 0;
    player[1].player_point.x = 50;
    player[1].player_point.y = 105;

    if(Player_number == 3){
        player[2].player_loc.x = 15;
        player[2].player_loc.y = 0;
        player[2].player_point.x = 920;
        player[2].player_point.y = 105;
    }
}

void PVP_map_initialize(int random_num){
    cout << "random = " << random_num << endl;
    if(random_num==0){
        map[3][0].wall = 1; map[6][0].wall = 1; map[7][0].wall = 1; map[8][0].wall = 1;
        map[2][1].wall = 1; map[3][1].wall = 1; map[3][1].wall = 1; map[6][1].wall = 1; map[7][1].wall = 1; map[8][1].wall = 1; map[10][1].wall = 1; map[11][1].wall = 1; map[12][1].wall = 1;
        map[1][4].wall = 1; map[4][4].wall = 1; map[5][4].wall = 1; map[6][4].wall = 1; map[9][4].wall = 1; map[10][4].wall = 1; map[11][4].wall = 1;
        map[1][5].wall = 1; map[4][5].wall = 1; map[5][5].wall = 1; map[6][5].wall = 1; map[9][5].wall = 1; map[10][5].wall = 1; map[11][5].wall = 1;
        map[0][6].wall = 1; map[9][6].wall = 1; map[11][6].wall = 1;
        map[0][8].wall = 1; map[1][8].wall = 1;
        map[0][9].wall = 1; map[1][9].wall = 1; map[4][9].wall = 1; map[7][9].wall = 1; map[8][9].wall = 1; map[12][9].wall = 1;
        map[4][10].wall = 1; map[7][10].wall = 1; map[8][10].wall = 1; map[12][10].wall = 1;

        PVP_background.loadFromFile("../PVP_image/background0.png");
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        PVP_background.render(NULL);
        SDL_RenderPresent( gRenderer );
    }
    else if(random_num==1){
        map[3][0].wall = 1; map[6][0].wall = 1; map[7][0].wall = 1; map[8][0].wall = 1;
        map[2][1].wall = 1; map[3][1].wall = 1; map[3][1].wall = 1; map[6][1].wall = 1; map[7][1].wall = 1; map[8][1].wall = 1; map[10][1].wall = 1; map[11][1].wall = 1; map[12][1].wall = 1;
        map[1][4].wall = 1; map[4][4].wall = 1; map[5][4].wall = 1; map[6][4].wall = 1; map[9][4].wall = 1; map[10][4].wall = 1; map[11][4].wall = 1;
        map[1][5].wall = 1; map[4][5].wall = 1; map[5][5].wall = 1; map[6][5].wall = 1; map[9][5].wall = 1; map[10][5].wall = 1; map[11][5].wall = 1;
        map[0][6].wall = 1; map[9][6].wall = 1; map[11][6].wall = 1;
        map[0][8].wall = 1; map[1][8].wall = 1;
        map[0][9].wall = 1; map[1][9].wall = 1; map[4][9].wall = 1; map[7][9].wall = 1; map[8][9].wall = 1; map[12][9].wall = 1;
        map[4][10].wall = 1; map[7][10].wall = 1; map[8][10].wall = 1; map[12][10].wall = 1;

        PVP_background.loadFromFile("../PVP_image/background0.png");
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        PVP_background.render(NULL);
        SDL_RenderPresent( gRenderer );
    }
    else if(random_num==2){
        map[3][0].wall = 1; map[6][0].wall = 1; map[7][0].wall = 1; map[8][0].wall = 1;
        map[2][1].wall = 1; map[3][1].wall = 1; map[3][1].wall = 1; map[6][1].wall = 1; map[7][1].wall = 1; map[8][1].wall = 1; map[10][1].wall = 1; map[11][1].wall = 1; map[12][1].wall = 1;
        map[1][4].wall = 1; map[4][4].wall = 1; map[5][4].wall = 1; map[6][4].wall = 1; map[9][4].wall = 1; map[10][4].wall = 1; map[11][4].wall = 1;
        map[1][5].wall = 1; map[4][5].wall = 1; map[5][5].wall = 1; map[6][5].wall = 1; map[9][5].wall = 1; map[10][5].wall = 1; map[11][5].wall = 1;
        map[0][6].wall = 1; map[9][6].wall = 1; map[11][6].wall = 1;
        map[0][8].wall = 1; map[1][8].wall = 1;
        map[0][9].wall = 1; map[1][9].wall = 1; map[4][9].wall = 1; map[7][9].wall = 1; map[8][9].wall = 1; map[12][9].wall = 1;
        map[4][10].wall = 1; map[7][10].wall = 1; map[8][10].wall = 1; map[12][10].wall = 1;

        PVP_background.loadFromFile("../PVP_image/background0.png");
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        PVP_background.render(NULL);
        SDL_RenderPresent( gRenderer );
    }
}

void PVP_Show_data(){
    for(int i = 0; i<Player_number; i++){

    }
}