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
Boss boss;

int PVE(){
    player = NULL;
    map = NULL;
    player = new Player[Player_number];
    for(int i = 0; i<Player_number; i++) player[i] = Player(i);
    player[0].count_rank = Player_number;
    map = new Map*[16];
    for(int i = 0; i<16; i++) {
        map[i] = new Map [11];
        for(int j = 0; j<11; j++){
            Location temp_loc(i,j);
            map[i][j] = Map(temp_loc);
        }
    }

    //for the boss to set bomb
    static int T = 10;

    PVE_map_initialize(0);

    PVE_initialize();

    CircleButton pause, music_on, music_off;
    SDL_Rect pause_dest = {870, 15, 50, 50}, music_dest = {930, 15, 50, 50};
    SDL_Point pause_cen = {895, 40}, music_cen = {955, 40};
    bool music = 1;
    pause = CircleButton(pause_dest, pause_cen, 25);
    music_on = CircleButton(music_dest, music_cen, 25);
    music_off = CircleButton(music_dest, music_cen, 25);
    pause.buttontexture.loadFromFile("../button_image/pause.png");
    music_on.buttontexture.loadFromFile("../button_image/music_on.png");
    music_off.buttontexture.loadFromFile("../button_image/music_off.png");

    Texture pause_black, pause_window;
    CircleButton pause_home, pause_restart, pause_quit;
    RectButton resume_button;
    SDL_Rect pausewindow_dest = {250, 140, 700, 470}, resume_dest = {380, 470, 440, 110},
            pausehome_dest = {370, 315, 140, 140}, pauserestart_dest = {530, 315, 140, 140}, pausequit_dest = {690, 315, 140, 140};
    SDL_Point pausehome_cen = {440, 385}, pauserestart_cen = {600, 385}, pausequit_cen = {760, 385};
    pause_home = CircleButton(pausehome_dest, pausehome_cen, 70);
    pause_restart = CircleButton(pauserestart_dest, pauserestart_cen, 70);
    pause_quit = CircleButton(pausequit_dest, pausequit_cen, 70);
    resume_button = RectButton(resume_dest);

    pause_black.loadFromFile("../button_image/pause_black.png");
    pause_black.setBlendMode(SDL_BLENDMODE_BLEND);
    pause_window.loadFromFile("../button_image/pause_window.png");
    pause_home.buttontexture.loadFromFile("../button_image/home.png");
    pause_restart.buttontexture.loadFromFile("../button_image/restart.png");
    pause_quit.buttontexture.loadFromFile("../button_image/quit.png");
    resume_button.buttontexture.loadFromFile("../button_image/resume.png");

    SDL_Rect blood_total = {390, 435, 220, 50}, blood_left = {400, 440, 200, 40};

    bomb_num = 0;
    bool keypress[12];
    bomb = NULL;

    clock_t start_time = clock();
    SDL_Event PVE_event;

    for(int i = 0; i<12; i++) keypress[i] = 0;
    while(!quit) {
        while (SDL_PollEvent(&PVE_event) != 0) {
            pause.handleEvent(&PVE_event);
            music_on.handleEvent(&PVE_event);
            music_off.handleEvent(&PVE_event);
            if (PVE_event.type == SDL_QUIT) {quit = true; return 3;}
            if (PVE_event.type == SDL_KEYDOWN && PVE_event.key.repeat==0) {
                switch( PVE_event.key.keysym.sym ){
                    case SDLK_UP: keypress[Key_Up] = 1; break;
                    case SDLK_DOWN: keypress[Key_Down] = 1; break;
                    case SDLK_LEFT: keypress[Key_Left] = 1; break;
                    case SDLK_RIGHT: keypress[Key_Right] = 1; break;
                    case SDLK_RETURN:
                        if(map[player[0].player_loc.x][player[0].player_loc.y].contain_bomb==0 && player[0].bomb_left>0 && player[0].alive){
                            bomb = *player[0].putbomb(&bomb);
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
                                bomb = *player[1].putbomb(&bomb);
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
                                bomb = *player[2].putbomb(&bomb);
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


            if(pause.CurrentSprite == BUTTON_SPRITE_MOUSE_DOWN) {
                bool resume = 0;
                cout << "pause " << endl;
                while(!resume){
                    SDL_Event pause_event;
                    while(1) {
                        while (SDL_PollEvent(&pause_event) != 0) {
                            pause_home.handleEvent(&pause_event);
                            pause_restart.handleEvent(&pause_event);
                            pause_quit.handleEvent(&pause_event);
                            resume_button.handleEvent(&pause_event);
                            if (pause_event.type == SDL_QUIT) {
                                quit = true;
                                return 3;
                            }
                            if (pause_home.CurrentSprite == BUTTON_SPRITE_MOUSE_UP) return 1;
                            if (pause_restart.CurrentSprite == BUTTON_SPRITE_MOUSE_UP) return 2;
                            if (pause_quit.CurrentSprite == BUTTON_SPRITE_MOUSE_UP) return 3;
                            if (resume_button.CurrentSprite == BUTTON_SPRITE_MOUSE_UP) {
                                cout << "resume" << endl;
                                resume = 1;
                                break;
                            }
                        }
                        if(resume) break;
                        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                        SDL_RenderClear(gRenderer);
                        PVE_background.render(NULL);

                        for (int i = 0; i < Player_number; i++) {
                            if (player[i].alive == 1) player[i].player_render();
                        }
                        for (int i = 0; i < 16; i++) {
                            for (int j = 0; j < 11; j++) map[i][j].render_map();
                        }
                        PVE_Show_data();

                        pause_black.setAlpha(150);
                        pause_black.render(NULL);

                        pause_window.render(&pausewindow_dest);

                        bool pausehome_big = 1, pauserestart_big = 1, pausequit_big = 1, pauseresume_big = 1;
                        if (pause_home.CurrentSprite == BUTTON_SPRITE_MOUSE_OUT) pausehome_big = 0;
                        pause_home.circlerender(pausehome_big);
                        if (pause_restart.CurrentSprite == BUTTON_SPRITE_MOUSE_OUT) pauserestart_big = 0;
                        pause_restart.circlerender(pauserestart_big);
                        if (pause_quit.CurrentSprite == BUTTON_SPRITE_MOUSE_OUT) pausequit_big = 0;
                        pause_quit.circlerender(pausequit_big);
                        if (resume_button.CurrentSprite == BUTTON_SPRITE_MOUSE_OUT) pauseresume_big = 0;
                        resume_button.rectrender(pauseresume_big);

                        SDL_RenderPresent(gRenderer);
                    }
                }
            }
            if(music_on.CurrentSprite == BUTTON_SPRITE_MOUSE_DOWN ) {
                while(music_on.CurrentSprite != BUTTON_SPRITE_MOUSE_UP) {
                    SDL_PollEvent(&PVE_event);
                    if (PVE_event.type == SDL_QUIT) {quit=true; break;}
                    music_on.handleEvent(&PVE_event);
                }
                if(music) music = 0;
                else music = 1;
            }
        }

        //pattern 1
        if(T % (300) ==0 &&  T % 900!=0) {
            int boss_bombx[3] = {10,11,12};
            int boss_bomby[3] = {2,  2, 2 };

            for(int i=0;i<3;i++){
                boss.player_loc.x = boss_bombx[i];
                boss.player_loc.y = boss_bomby[i];
                *boss.putbomb(&bomb);
                boss.bomb_left --;
            }
        }
        //pattern 2
        if(T % (300) ==0 && T % 900!=0) {
            int boss_bombx[3] = { 3, 4, 5};
            int boss_bomby[3] = { 7, 7, 7};

            for(int i=0;i<3;i++){
                boss.player_loc.x = boss_bombx[i];
                boss.player_loc.y = boss_bomby[i];
                *boss.putbomb(&bomb);
                boss.bomb_left --;
            }
        }
        //pattern 3
        if(T % (900) ==0) {
            int boss_bombx[3] = { 1, 2, 3};
            int boss_bomby[3] = { 2, 2, 2 };

            for(int i=0;i<3;i++){
                boss.player_loc.x = boss_bombx[i];
                boss.player_loc.y = boss_bomby[i];
                *boss.putbomb(&bomb);
                boss.bomb_left --;
            }
        }
        //pattern 4
        if(T % (900) ==0) {
            int boss_bombx[3] = { 14, 9, 4};
            int boss_bomby[3] = { 7,  8, 10};

            for(int i=0;i<3;i++){
                boss.player_loc.x = boss_bombx[i];
                boss.player_loc.y = boss_bomby[i];
                *boss.putbomb(&bomb);
                boss.bomb_left --;
            }
        }
        if(boss.boss_life < 15 && T%1000 == 0){

            boss.player_loc.x = 13;
            boss.player_loc.y =  3;
            *boss.putbomb(&bomb);
            boss.bomb_left --;
        }
        if(boss.boss_life < 15 ){
            if(T % 1200 == 0&& T % 600 != 0){
                boss.player_loc.x = 7;
                boss.player_loc.y =  1;
                *boss.putbomb(&bomb);
                boss.bomb_left --;
            }
            else if(T % 600 == 0){
                boss.player_loc.x = 7;
                boss.player_loc.y =  0;
                *boss.putbomb(&bomb);
                boss.bomb_left --;
            }
        }


        if (keypress[Key_Up]) player[0].move(UP);
        else if (keypress[Key_Down]) player[0].move(DOWN);
        else if (keypress[Key_Left]) player[0].move(LEFT);
        else if (keypress[Key_Right]) player[0].move(RIGHT);
        else player[0].finish_moving();

        if(Player_number > 1){
            if (keypress[Key_w]) player[1].move(UP);
            else if (keypress[Key_s]) player[1].move(DOWN);
            else if (keypress[Key_a]) player[1].move(LEFT);
            else if (keypress[Key_d]) player[1].move(RIGHT);
            else player[1].finish_moving();

            if(Player_number == 3){
                if (keypress[Key_i]) player[2].move(UP);
                else if (keypress[Key_k]) player[2].move(DOWN);
                else if (keypress[Key_j]) player[2].move(LEFT);
                else if (keypress[Key_l]) player[2].move(RIGHT);
                else player[2].finish_moving();
            }
        }
        for(int i = 0; i<bomb_num; i++){
            if(double(clock() - bomb[i].clk)/CLOCKS_PER_SEC > 2.7){
                bomb = *bomb[i].bomb_explode(i, &bomb);
                i--;
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        PVE_background.render(NULL);

        bool bigpause=1, bigmusic=1;
        if(pause.CurrentSprite == BUTTON_SPRITE_MOUSE_OUT) bigpause = 0;
        pause.circlerender(bigpause);
        if(music_on.CurrentSprite == BUTTON_SPRITE_MOUSE_OUT ) bigmusic = 0;
        if(music) music_on.circlerender(bigmusic);
        else music_off.circlerender(bigmusic);


        bool game_continue = 0;
        for(int i = 0; i<Player_number; i++) {
            if(player[i].alive==1) {
                player[i].player_render();
                game_continue = 1;
            }
        }
        if(boss.boss_life <= 0){
            game_continue = 0;
            SDL_Delay(1000);
            return 4;
        }

        boss.player_render();
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
        SDL_RenderFillRect(gRenderer, &blood_total);

        if(Player_number==1){
            blood_left.w = (boss.boss_life/50.0) * 200;
        }
        else if(Player_number==2){
            blood_left.w = (boss.boss_life/70.0) * 200;
        }
        else if(Player_number==3){
            blood_left.w = (boss.boss_life/90.0) * 200;
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(gRenderer, &blood_left);

        for(int i = 0; i<16; i++){
            for(int j = 0; j<11; j++){
                map[i][j].render_map();
            }
        }
        static int flag[3] = {0};
        if(boss.boss_life <=40){
            if(flag[0]==0){
                cout << "haha" << endl;
                T=10;
                flag[0] = 1;
            }
            T += 2;
        }
        else if(boss.boss_life <=30){
            if(flag[1]==0){
                T=10;
                flag[1] = 1;
            }
            T += 5;
        }
        else if(boss.boss_life <=15){
            if(flag[2]==0){
                T=10;
                flag[2] = 1;
            }
            T += 10;
        }
        else T++;

        cout << "T is " << T << endl;
        cout << "boss' left life is  " << boss.boss_life << endl;


        PVE_Show_data();

        //每秒不知道多少
        //int time = (clock()- start_time)/70000;
        //cout << time << endl;

        SDL_RenderPresent(gRenderer);
        if(!game_continue) {
            SDL_Delay(1000);
            break;
        }
    }
    delete [] bomb;
    for(int i = 0; i<16; i++) delete [] map[i];
    delete [] map;
    if(boss.boss_life==0) return 4;
    else return 0;
}

void PVE_initialize(){
    bomb_texture.loadFromFile("../item_image/bomb.png");
    emptybox_texture.loadFromFile("../item_image/empty_box.png");
    explode_texture.loadFromFile("../item_image/explode.png");
    cross_texture.loadFromFile("../item_image/cross.png");
    explode_texture.setBlendMode( SDL_BLENDMODE_BLEND );

    //item_texture.loadFromFile

    item_texture[0].loadFromFile("../item_image/item0.png");
    item_texture[1].loadFromFile("../item_image/item1.png");
    item_texture[2].loadFromFile("../item_image/item2.png");
    item_texture[3].loadFromFile("../item_image/item3.png");
    item_texture[4].loadFromFile("../item_image/item4_PVE.png");
    item_texture[5].loadFromFile("../item_image/item5.png");
    item_texture[11].loadFromFile("../item_image/item11_PVE.png");

    boss.picture.loadFromFile("../character_image/boss.png");
    boss.bomb_distance = 16;
    boss.bomb_available = 100;
    boss.bomb_left =  100;
    if(Player_number==1) boss.boss_life = 50;
    else if(Player_number==2) boss.boss_life = 70;
    else if(Player_number==3) boss.boss_life = 90;

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
        map[1][0].wall = map[2][0].wall = map[11][0].wall = map[12][0].wall = map[13][0].wall = 1;
        map[12][1].wall = 1;
        map[4][2].wall = map[5][2].wall = 1;
        map[6][3].wall = map[7][3].wall = map[8][3].wall = map[9][3].wall = map[14][3].wall = map[15][3].wall = 1;
        map[2][4].wall = map[3][4].wall = map[6][4].wall = map[7][4].wall = map[8][4].wall = map[9][4].wall = map[13][4].wall = map[14][4].wall = 1;
        map[3][5].wall = map[6][5].wall = map[7][5].wall = map[8][5].wall = map[9][5].wall = 1;
        map[3][6].wall = map[6][6].wall = map[7][6].wall = map[8][6].wall = map[9][6].wall = 1;
        map[15][7].wall = 1;
        map[0][8].wall = map[15][8].wall = 1;
        map[0][9].wall = map[1][9].wall = map[0][9].wall = map[7][9].wall = map[14][9].wall = map[15][9].wall = 1;
        map[0][10].wall = map[7][10].wall = map[9][10].wall = map[10][10].wall = map[11][10].wall = 1;
//
        //here's the locations of items
        map[3][0].contain_item  =  map[6][0].contain_item  = 1;
        map[1][1].contain_item =  map[5][1].contain_item = map[8][1].contain_item = map[13][1].contain_item =1;
        map[7][2].contain_item  = map[14][2].contain_item = 1;
        map[0][3].contain_item =  map[1][3].contain_item = map[12][3].contain_item =1;
        //map[0][4].contain_item = map[2][4].contain_item = map[7][4].contain_item = map[8][4].contain_item = 1;
        map[2][5].contain_item = map[10][5].contain_item = map[13][5].contain_item = map[15][5].contain_item = 1;
        map[1][6].contain_item =  map[11][6].contain_item = map[13][6].contain_item = 1;
        map[7][7].contain_item =map[10][7].contain_item =map[13][7].contain_item = 1;
        map[2][8].contain_item = map[6][8].contain_item = 1;
        map[3][9].contain_item = map[11][9].contain_item = map[13][9].contain_item = 1;
        map[5][10].contain_item = 1;

        //here's the locations of box with items
        map[3][0].contain_emptybox  =  map[6][0].contain_emptybox  = 1;
        map[1][1].contain_emptybox =  map[5][1].contain_emptybox = map[8][1].contain_emptybox = map[13][1].contain_emptybox =1;
        map[7][2].contain_emptybox = map[14][2].contain_emptybox = 1;
        map[0][3].contain_emptybox =  map[1][3].contain_emptybox = map[12][3].contain_emptybox =1;
        //map[0][4].contain_emptybox = map[2][4].contain_emptybox = map[7][4].contain_emptybox = map[8][4].contain_emptybox = 1;
        map[2][5].contain_emptybox = map[10][5].contain_emptybox = map[13][5].contain_emptybox = map[15][5].contain_emptybox = 1;
        map[1][6].contain_emptybox = map[11][6].contain_emptybox = map[13][6].contain_emptybox = 1;
        map[7][7].contain_emptybox = map[10][7].contain_emptybox = map[13][7].contain_emptybox = 1;
        map[2][8].contain_emptybox = map[6][8].contain_emptybox = 1;
        map[3][9].contain_emptybox = map[11][9].contain_emptybox = map[13][9].contain_emptybox = 1;
        map[5][10].contain_emptybox = 1;

        int item0x[3] = { 0, 13, 2};
        int item0y[3] = { 3,  7, 8};
        for(int i = 0; i < 3; i++) {
            map[item0x[i]][item0y[i]].which_item = 0;
        }

        int  item1x[4] = {13, 15,  1, 11};
        int  item1y[4] = { 1,  5,  6,  6};
        for(int i = 0; i<4; i++) {
            map[item1x[i]][item1y[i]].which_item = 1;
        }

        int  item2x[2] = {5, 7};
        int  item2y[2] = {1, 7};
        for(int i = 0; i<2; i++) {
            map[item2x[i]][item2y[i]].which_item = 2;
        }

        int  item3x[3] = {3, 3, 13};
        int  item3y[3] = {0, 9,  9};
        for(int i = 0; i<3; i++) {
            map[item3x[i]][item3y[i]].which_item = 3;
        }

        int  item4x[3]= { 2, 10, 13};
        int  item4y[3]= { 5, 5,   5};
        for(int i = 0; i<3; i++) {
            map[item4x[i]][item4y[i]].which_item = 4;
        }

        int  item5x[7] = { 6, 7, 1, 12, 13, 10,  5};
        int  item5y[7] = { 0, 2, 3,  3,  6,  7, 10};
        for(int i = 0; i < 7; i++) {
            map[item5x[i]][item5y[i]].which_item = 5;
        }

        int  item11x[5] = { 1, 8, 14,  6, 11};
        int  item11y[5] = { 1, 1,  2,  8,  9};
        for(int i = 0; i<5; i++) {
            map[item11x[i]][item11y[i]].which_item = 11;
        }

        for(int i = 6; i < 10; i++) {
            for (int j = 3; j < 7; j++) {
                map[i][j].wall = 1;
            }
        }

        //map[5][3].contain_emptybox = map[10][8].contain_emptybox =map[7][4].contain_emptybox = map[2][9].contain_emptybox =  1;

        for(int i = 0; i<16; i++) {
            for (int j = 0; j < 11; j++) {
                if (map[i][j].contain_emptybox == 1) map[i][j].emptybox = new empty_box;
                if (map[i][j].contain_item == 1) {
                    Location temp(i, j);
                    map[i][j].item = new Item(temp, map[i][j].which_item);
                }
            }
        }


        PVE_background.loadFromFile("../PVE_image/background0.png");
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        PVE_background.render(NULL);
        SDL_RenderPresent( gRenderer );
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
        for(int j = 0; j<12; j++){
            if(player[i].item[j]==1) item_texture[j].render(&player_item[i][j]);
        }
        if(player[i].alive == 0) cross_texture.render(&photo_sticker[i]);
    }
}