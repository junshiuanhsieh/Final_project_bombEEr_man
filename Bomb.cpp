#include "Bomb.h"
#include "Map.h"
#include "Player.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Renderer* gRenderer;
extern int Player_number, Mode;
extern int* character_picture;
extern const int Total_item;
extern Map** map;
extern Player* player;
extern int bomb_num;

Bomb::Bomb() : clk(clock()){
    bomb_distance = 1;
}
Bomb::Bomb(Location loc, int distance, int player_num, int _number) : bomb_loc(loc), bomb_distance(distance){
    clk = clock();
    owner = player_num;
    number = _number;
}
Bomb::Bomb(const Bomb &copy): clk(copy.clk){
    bomb_loc = copy.bomb_loc;
    bomb_distance = copy.bomb_distance;
    owner = copy.owner;
    number = copy.number;
}
Bomb Bomb::operator=(const Bomb & copy){
    clk = copy.clk;
    bomb_loc = copy.bomb_loc;
    bomb_distance = copy.bomb_distance;
    owner = copy.owner;
    number = copy.number;
}

int Bomb::bomb_up(Bomb* bomb){
    Location bombUp = bomb_loc;
    for(int i = 1; i<=bomb_distance; i++){
        if(bomb_loc.y-i < 0) {
            return i-1;
        }
        bombUp.y = bomb_loc.y - i;
        for(int j = 0; j<Player_number; j++){
            if (map[bombUp.x][bombUp.y].character_inside[j] && player[j].alive==1){
                player[j].dead();
                cout << "player" << j << " died! " << endl;
                return i;
            }
        }
        if(map[bombUp.x][bombUp.y].wall) {
            return i-1;
        }
        else if(map[bombUp.x][bombUp.y].contain_bomb){
            //map[bombUp.x][bombUp.y].bomb->bomb_explode(map[bombUp.x][bombUp.y].bomb->number, bomb);
            return i;
        }
        else if(map[bombUp.x][bombUp.y].contain_emptybox){
            map[bombUp.x][bombUp.y].collapse();
            return i;
        }
        else if(map[bombUp.x][bombUp.y].contain_item && map[bombUp.x][bombUp.y].item->destroyed==0){
            map[bombUp.x][bombUp.y].collapse();
            return i;
        }
    }
    return bomb_distance;
}
int Bomb::bomb_down(Bomb* bomb){
    Location bombDown = bomb_loc;
    for(int i = 1; i<=bomb_distance; i++){
        if(bomb_loc.y+i > 10) {
            return i-1;
        }
        bombDown.y = bomb_loc.y + i;
        for(int j = 0; j<Player_number; j++){
            if (map[bombDown.x][bombDown.y].character_inside[j] && player[j].alive==1){
                player[j].dead();
                cout << "player" << j << " died! " << endl;
                return i;
            }
        }
        if(map[bombDown.x][bombDown.y].wall) {
            return i-1;
        }
        else if(map[bombDown.x][bombDown.y].contain_bomb){
            //map[bombDown.x][bombDown.y].bomb->bomb_explode(map[bombDown.x][bombDown.y].bomb->number, bomb);
            return i;
        }
        else if(map[bombDown.x][bombDown.y].contain_emptybox){
            map[bombDown.x][bombDown.y].collapse();
            return i;
        }
        else if(map[bombDown.x][bombDown.y].contain_item && map[bombDown.x][bombDown.y].item->destroyed==0){
            map[bombDown.x][bombDown.y].collapse();
            return i;
        }
    }
    return bomb_distance;
}
int Bomb::bomb_left(Bomb* bomb){
    Location bombLeft = bomb_loc;
    for(int i = 1; i<=bomb_distance; i++){
        if(bomb_loc.x-i < 0) {
            return i-1;
        }
        bombLeft.x = bomb_loc.x - i;
        for(int j = 0; j<Player_number; j++){
            if (map[bombLeft.x][bombLeft.y].character_inside[j] && player[j].alive==1){
                player[j].dead();
                cout << "player" << j << " died! " << endl;
                return i;
            }
        }
        if(map[bombLeft.x][bombLeft.y].wall) {
            return i-1;
        }
        else if(map[bombLeft.x][bombLeft.y].contain_bomb){
            //map[bombLeft.x][bombLeft.y].bomb->bomb_explode(map[bombLeft.x][bombLeft.y].bomb->number, bomb);
            return i;
        }
        else if(map[bombLeft.x][bombLeft.y].contain_emptybox){
            map[bombLeft.x][bombLeft.y].collapse();
            return i;
        }
        else if(map[bombLeft.x][bombLeft.y].contain_item && map[bombLeft.x][bombLeft.y].item->destroyed==0){
            map[bombLeft.x][bombLeft.y].collapse();
            return i;
        }
    }
    return bomb_distance;
}
int Bomb::bomb_right(Bomb* bomb){
    Location bombRight = bomb_loc;
    for(int i = 1; i<=bomb_distance; i++){
        if(bomb_loc.x+i > 15) {
            return i-1;
        }
        bombRight.x = bomb_loc.x + i;
        for(int j = 0; j<Player_number; j++){
            if (map[bombRight.x][bombRight.y].character_inside[j] && player[j].alive==1){
                player[j].dead();
                cout << "player" << j << " died! " << endl;
                return i;
            }
        }
        if(map[bombRight.x][bombRight.y].wall) {
            return i-1;
        }
        else if(map[bombRight.x][bombRight.y].contain_bomb){
           // map[bombRight.x][bombRight.y].bomb->bomb_explode(map[bombRight.x][bombRight.y].bomb->number, bomb);
            return i;
        }
        else if(map[bombRight.x][bombRight.y].contain_emptybox){
            map[bombRight.x][bombRight.y].collapse();
            return i;
        }
        else if(map[bombRight.x][bombRight.y].contain_item && map[bombRight.x][bombRight.y].item->destroyed==0){
            map[bombRight.x][bombRight.y].collapse();
            return i;
        }
    }
    return bomb_distance;
}

Bomb* Bomb::bomb_explode(int num, Bomb * bomb){
    clk = 0;
    changemap(bomb);
    bomb_num--;
    Bomb* temp_bomb;
    temp_bomb= new Bomb [bomb_num];
    Bomb* temptempbomb;
    temptempbomb = bomb;
    for(int i = 0; i<num; i++) temp_bomb[i] = Bomb(bomb[i]);
    for(int i = num; i<bomb_num; i++) {
        temp_bomb[i] = Bomb(bomb[i+1]);
        temp_bomb[i].number--;
    }
    bomb = temp_bomb;
    temp_bomb = temptempbomb;
    map[bomb_loc.x][bomb_loc.y].contain_bomb = 0;
    map[bomb_loc.x][bomb_loc.y].bomb = NULL;
    player[owner].bomb_left++;
    delete [] temp_bomb;
    return bomb;
}

void Bomb::changemap(Bomb* bomb){
    int bomb_farest[4];
    bool bomb_on_character = 0;
    for(int i = 0; i<Player_number; i++){
        if(map[bomb_loc.x][bomb_loc.y].character_inside[i] && player[i].alive) {
            bomb_on_character = 1;
            player[i].dead();
            cout << "player" << i << " died!" << endl;
        }
        bomb_farest[UP] = bomb_farest[DOWN] = bomb_farest[LEFT] = bomb_farest[RIGHT] = 0;
    }
    if(!bomb_on_character){
        bomb_farest[UP] = bomb_up(bomb);
        bomb_farest[DOWN] = bomb_down(bomb);
        bomb_farest[LEFT] = bomb_left(bomb);
        bomb_farest[RIGHT] = bomb_right(bomb);
    }

    map[bomb_loc.x][bomb_loc.y].explode_blending = 255;

    for(int i = 1; i<=bomb_farest[UP]; i++){
        map[bomb_loc.x][bomb_loc.y-i].explode_blending = 255;
    }
    for(int i = 1; i<=bomb_farest[DOWN]; i++){
        map[bomb_loc.x][bomb_loc.y+i].explode_blending = 255;
    }
    for(int i = 1; i<=bomb_farest[LEFT]; i++){
        map[bomb_loc.x-i][bomb_loc.y].explode_blending = 255;
    }
    for(int i = 1; i<=bomb_farest[RIGHT]; i++){
        map[bomb_loc.x+i][bomb_loc.y].explode_blending = 255;
    }
}
