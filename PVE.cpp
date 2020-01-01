#include "PVE.h"
#include <cstdlib>
#include <ctime>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Renderer* gRenderer;
extern bool quit;
extern int Player_number, Mode;
extern const int Total_item;
extern int* character_picture;
extern Player* player;
extern Map** map;
extern Bomb* bomb;
extern Texture bomb_texture, emptybox_texture, item_texture[12], itembox_texture, explode_texture, cross_texture;
Texture PVE_background;
int bomb_num = 0;

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

    PVE_initialize();

    int rate = 10;
    bomb_num = 0;
    bool keypress[12];
    Bomb * bomb = NULL;
    SDL_Event PVE_event;

    for(int i = 0; i<12; i++) keypress[i] = 0;
    while(!quit) {
        while (SDL_PollEvent(&PVE_event) != 0) {
            if (PVE_event.type == SDL_QUIT) {quit = true; return;}
            if (PVE_event.type == SDL_KEYDOWN && PVE_event.key.repeat==0) {
                switch( PVE_event.key.keysym.sym ){
                    case SDLK_UP: keypress[Key_Up] = 1; break;
                    case SDLK_DOWN: keypress[Key_Down] = 1; break;
                    case SDLK_LEFT: keypress[Key_Left] = 1; break;
                    case SDLK_RIGHT: keypress[Key_Right] = 1; break;
                    case SDLK_RETURN:
                        if(map[player[0].player_loc.x][player[0].player_loc.y].contain_bomb==0 && player[0].bomb_left>0 && player[0].alive){
                            bomb = player[0].putbomb(bomb);
                            player[0].bomb_left--;
                        }
                        break;

                    case SDLK_w: keypress[Key_w] = 1; break;
                    case SDLK_s: keypress[Key_s] = 1; break;
                    case SDLK_a: keypress[Key_a] = 1; break;
                    case SDLK_d: keypress[Key_d] = 1; break;
                    case SDLK_TAB:
                        if(Player_number > 1) {
                            if (map[player[1].player_loc.x][player[1].player_loc.y].contain_bomb == 0 && player[1].bomb_left>0 && player[1].alive){
                                bomb = player[1].putbomb(bomb);
                                player[1].bomb_left--;
                            }
                        }
                        break;

                    case SDLK_i: keypress[Key_i] = 1; break;
                    case SDLK_k: keypress[Key_k] = 1; break;
                    case SDLK_j: keypress[Key_j] = 1; break;
                    case SDLK_l: keypress[Key_l] = 1; break;
                    case SDLK_SPACE:
                        if(Player_number == 3) {
                            if (map[player[2].player_loc.x][player[2].player_loc.y].contain_bomb == 0 && player[2].bomb_left>0 && player[2].alive){
                                bomb = player[2].putbomb(bomb);
                                player[2].bomb_left--;
                            }
                        }
                        break;
                }
            }
            else if (PVE_event.type == SDL_KEYUP && PVE_event.key.repeat==0) {
                switch( PVE_event.key.keysym.sym ){
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

        if(Player_number > 1){
            if (keypress[Key_w]) player[1].move(UP, rate);
            else if (keypress[Key_s]) player[1].move(DOWN, rate);
            else if (keypress[Key_a]) player[1].move(LEFT, rate);
            else if (keypress[Key_d]) player[1].move(RIGHT, rate);
            else player[1].finish_moving();

            if(Player_number == 3){
                if (keypress[Key_i]) player[2].move(UP, rate);
                else if (keypress[Key_k]) player[2].move(DOWN, rate);
                else if (keypress[Key_j]) player[2].move(LEFT, rate);
                else if (keypress[Key_l]) player[2].move(RIGHT, rate);
                else player[2].finish_moving();
            }
        }
        for(int i = 0; i<bomb_num; i++){
            if(clock() - bomb[i].clk > 100000){
                bomb = bomb[i].bomb_explode(i, bomb);
                i--;
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        PVE_background.render(NULL);
        for(int i = 0; i<16; i++){
            for(int j = 0; j<11; j++){
                map[i][j].render_map();
            }
        }
        for(int i = 0; i<Player_number; i++) if(player[i].alive==1) player[i].player_render();
        PVE_Show_data();

        SDL_RenderPresent(gRenderer);
    }
}

void PVE_initialize(){
    bomb_texture.loadFromFile("../item_image/bomb.png");
    itembox_texture.loadFromFile("../item_image/box.png");
    emptybox_texture.loadFromFile("../item_image/empty_box.png");
    explode_texture.loadFromFile("../item_image/explode.png");
    cross_texture.loadFromFile("../item_image/cross.png");
    explode_texture.setBlendMode( SDL_BLENDMODE_BLEND );
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
    map[15][10].character_inside[0] = 1;

    if(Player_number>1){
        player[1].player_loc.x = 0;
        player[1].player_loc.y = 0;
        player[1].player_point.x = 50;
        player[1].player_point.y = 105;
        map[0][0].character_inside[1] = 1;

        if(Player_number == 3){
            player[2].player_loc.x = 15;
            player[2].player_loc.y = 0;
            player[2].player_point.x = 920;
            player[2].player_point.y = 105;
            map[15][0].character_inside[2] = 1;
        }
    }
}
void PVE_map_initialize(int random_num){
    cout << "random = " << random_num << endl;
    if(random_num==0){
        map[3][0].wall = map[6][0].wall = map[7][0].wall = map[8][0].wall = 1;
        map[2][1].wall = map[3][1].wall = map[3][1].wall = map[6][1].wall = map[7][1].wall = map[8][1].wall = map[10][1].wall = map[11][1].wall = map[12][1].wall = 1;
        map[1][4].wall = map[4][4].wall = map[5][4].wall = map[6][4].wall = map[9][4].wall = map[10][4].wall = map[11][4].wall = 1;
        map[1][5].wall = map[4][5].wall = map[5][5].wall = map[6][5].wall = map[9][5].wall = map[10][5].wall = map[11][5].wall = 1;
        map[0][6].wall = map[9][6].wall = map[11][6].wall = 1;
        map[0][8].wall = map[1][8].wall = 1;
        map[0][9].wall = map[1][9].wall = map[4][9].wall = map[7][9].wall = map[8][9].wall = map[12][9].wall = 1;
        map[4][10].wall = map[7][10].wall = map[8][10].wall = map[12][10].wall = 1;

        PVE_background.loadFromFile("../PVP_image/background0.png");
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        PVE_background.render(NULL);
        SDL_RenderPresent( gRenderer );
    }
    else if(random_num==1){
        map[3][0].wall = map[6][0].wall = map[7][0].wall = map[8][0].wall = 1;
        map[2][1].wall = map[3][1].wall = map[3][1].wall = map[6][1].wall = map[7][1].wall = map[8][1].wall = map[10][1].wall = map[11][1].wall = map[12][1].wall = 1;
        map[1][4].wall = map[4][4].wall = map[5][4].wall = map[6][4].wall = map[9][4].wall = map[10][4].wall = map[11][4].wall = 1;
        map[1][5].wall = map[4][5].wall = map[5][5].wall = map[6][5].wall = map[9][5].wall = map[10][5].wall = map[11][5].wall = 1;
        map[0][6].wall = map[9][6].wall = map[11][6].wall = 1;
        map[0][8].wall = map[1][8].wall = 1;
        map[0][9].wall = map[1][9].wall = map[4][9].wall = map[7][9].wall = map[8][9].wall = map[12][9].wall = 1;
        map[4][10].wall = map[7][10].wall = map[8][10].wall = map[12][10].wall = 1;

        PVE_background.loadFromFile("../PVP_image/background0.png");
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        PVE_background.render(NULL);
        SDL_RenderPresent( gRenderer );
    }
    else if(random_num==2){
        map[3][0].wall = map[6][0].wall = map[7][0].wall = map[8][0].wall = 1;
        map[2][1].wall = map[3][1].wall = map[3][1].wall = map[6][1].wall = map[7][1].wall = map[8][1].wall = map[10][1].wall = map[11][1].wall = map[12][1].wall = 1;
        map[1][4].wall = map[4][4].wall = map[5][4].wall = map[6][4].wall = map[9][4].wall = map[10][4].wall = map[11][4].wall = 1;
        map[1][5].wall = map[4][5].wall = map[5][5].wall = map[6][5].wall = map[9][5].wall = map[10][5].wall = map[11][5].wall = 1;
        map[0][6].wall = map[9][6].wall = map[11][6].wall = 1;
        map[0][8].wall = map[1][8].wall = 1;
        map[0][9].wall = map[1][9].wall = map[4][9].wall = map[7][9].wall = map[8][9].wall = map[12][9].wall = 1;
        map[4][10].wall = map[7][10].wall = map[8][10].wall = map[12][10].wall = 1;

        PVE_background.loadFromFile("../PVP_image/background0.png");
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        PVE_background.render(NULL);
        SDL_RenderPresent(gRenderer);
    }
}
void PVE_Show_data(){
    static SDL_Rect photo_sticker[3] = {{1000,0,100,100}, {1000,250,100,100}, {1000,500,100,100}};
    static SDL_Rect score[3] = {{1100,0,100,100}, {1100,250,100,100}, {1100,500,100,100}};
    SDL_Rect player_item[Player_number][12];
    for(int i = 0; i<Player_number; i++){
        for(int j = 0; j<3; j++){
            for(int k = 0; k<4; k++){
                player_item[i][k+4*j].x = 1000 + 50*k;
                player_item[i][k+4*j].y = 250*i + 100 + 50*j;
                player_item[i][k+4*j].w = player_item[i][k+4*j].h = 50;
            }
        }
        player[i].picture.render(&photo_sticker[i]);
//        for(int j = 0; j<12; j++){
//            if(player[i].item[j])
//        }
        if(player[i].alive == 0) cross_texture.render(&photo_sticker[i]);
    }
}