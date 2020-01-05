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
extern Bomb * bomb;  //一開始不知道為什麼會是NULL，沒有跟其他cpp檔連結，小心使用，有時間的話網路上說用用看singleton
extern Boss boss;
Bomb::Bomb() : clk(clock()){
    bomb_distance = 1;
}
Bomb::Bomb(Location loc, int distance, int player_num, int _number) : clk(clock()), bomb_loc(loc), bomb_distance(distance){
    owner = player_num;
    number = _number;
    map[bomb_loc.x][bomb_loc.y].bomb = this;
}
Bomb::Bomb(const Bomb &copy): clk(copy.clk){
    bomb_loc = copy.bomb_loc;
    bomb_distance = copy.bomb_distance;
    owner = copy.owner;
    number = copy.number;
    map[bomb_loc.x][bomb_loc.y].bomb = this;
}
Bomb Bomb::operator=(const Bomb & copy){
    clk = copy.clk;
    bomb_loc = copy.bomb_loc;
    bomb_distance = copy.bomb_distance;
    owner = copy.owner;
    number = copy.number;
    map[bomb_loc.x][bomb_loc.y].bomb = this;
}
int Bomb::bomb_up(){
    Location bombUp = bomb_loc;
    for(int i = 1; i<=bomb_distance; i++){
        if(bomb_loc.y-i < 0) return i-1;
        bombUp.y = bomb_loc.y - i;
        for(int j = 0; j<Player_number; j++){
            if (map[bombUp.x][bombUp.y].character_inside[j] && player[j].alive==1 && player[j].item[11] ==0){
                player[j].dead();
                cout << "player" << j << " died! " << endl;
                //if(!map[bombUp.x][bombUp.y].contain_bomb)
                    return i;
            }
            else if(map[bombUp.x][bombUp.y].character_inside[j] && player[j].alive==1 && player[j].item[11] ==1){
                player[j].item[11] = 0;
            }
        }
        if(map[bombUp.x][bombUp.y].contain_bomb){
           // bomb = map[bombUp.x][bombUp.y].bomb->bomb_explode(map[bombUp.x][bombUp.y].bomb->number, bomb);
            return i;
        }
        else if(map[bombUp.x][bombUp.y].wall) {
            if(Mode == 1 &&bombUp.x <=9 && bombUp.x >=6 &bombUp.y >=3 & bombUp.y <= 6){
                boss.boss_life--;
            }
            return i-1;
        }
        else if(map[bombUp.x][bombUp.y].contain_emptybox){
            map[bombUp.x][bombUp.y].collapse();
            return i;
        }
//        else if(map[bombUp.x][bombUp.y].contain_item && map[bombUp.x][bombUp.y].item->destroyed==0){
//            map[bombUp.x][bombUp.y].collapse();
//            return i;
//        }
    }
    return bomb_distance;
}
int Bomb::bomb_down(){
    Location bombDown = bomb_loc;
    for(int i = 1; i<=bomb_distance; i++){
        if(bomb_loc.y+i > 10) return i-1;
        bombDown.y = bomb_loc.y + i;
        for(int j = 0; j<Player_number; j++){
            if (map[bombDown.x][bombDown.y].character_inside[j] && player[j].alive==1 && player[j].item[11] ==0){
                player[j].dead();
                cout << "player" << j << " died! " << endl;
               // if(!map[bombDown.x][bombDown.y].contain_bomb)
                    return i;
            }
            else if(map[bombDown.x][bombDown.y].character_inside[j] && player[j].alive==1 && player[j].item[11] ==1){
                player[j].item[11] = 0;
            }
        }
        if(map[bombDown.x][bombDown.y].contain_bomb){
            //bomb = map[bombDown.x][bombDown.y].bomb->bomb_explode(map[bombDown.x][bombDown.y].bomb->number, bomb);
            return i;
        }
        else if(map[bombDown.x][bombDown.y].wall) {
            if(Mode == 1 &&bombDown.x <=9 && bombDown.x >=6 &bombDown.y >=3 & bombDown.y <= 6){
                boss.boss_life--;
            }
            return i-1;
        }
        else if(map[bombDown.x][bombDown.y].contain_emptybox){
            map[bombDown.x][bombDown.y].collapse();
            return i;
        }
//        else if(map[bombDown.x][bombDown.y].contain_item && map[bombDown.x][bombDown.y].item->destroyed==0){
//            map[bombDown.x][bombDown.y].collapse();
//            return i;
//        }
    }
    return bomb_distance;
}
int Bomb::bomb_left(){
    Location bombLeft = bomb_loc;
    for(int i = 1; i<=bomb_distance; i++){
        if(bomb_loc.x-i < 0) return i-1;
        bombLeft.x = bomb_loc.x - i;
        for(int j = 0; j<Player_number; j++){
            if (map[bombLeft.x][bombLeft.y].character_inside[j] && player[j].alive==1 && player[j].item[11] ==0){
                player[j].dead();
                cout << "player" << j << " died! " << endl;
                //if(!map[bombLeft.x][bombLeft.y].contain_bomb)
                    return i;
            }
            else if(map[bombLeft.x][bombLeft.y].character_inside[j] && player[j].alive==1 && player[j].item[11] ==1){
                player[j].item[11] = 0;
            }
        }
        if(map[bombLeft.x][bombLeft.y].contain_bomb){
            //bomb = map[bombLeft.x][bombLeft.y].bomb->bomb_explode(map[bombLeft.x][bombLeft.y].bomb->number, bomb);
            return i;
        }
        else if(map[bombLeft.x][bombLeft.y].wall) {
            if(Mode == 1 &&bombLeft.x <=9 && bombLeft.x >=6 &bombLeft.y >=3 & bombLeft.y <= 6){
                boss.boss_life--;
            }
            return i-1;
        }
        else if(map[bombLeft.x][bombLeft.y].contain_emptybox){
            map[bombLeft.x][bombLeft.y].collapse();
            return i;
        }
//        else if(map[bombLeft.x][bombLeft.y].contain_item && map[bombLeft.x][bombLeft.y].item->destroyed==0){
//            map[bombLeft.x][bombLeft.y].collapse();
//            return i;
//        }
    }
    return bomb_distance;
}
int Bomb::bomb_right(){
    Location bombRight = bomb_loc;
    for(int i = 1; i<=bomb_distance; i++){
        if(bomb_loc.x+i > 15) return i-1;
        bombRight.x = bomb_loc.x + i;
        for(int j = 0; j<Player_number; j++){
            if (map[bombRight.x][bombRight.y].character_inside[j] && player[j].alive==1 && player[j].item[11] ==0){
                player[j].dead();
                cout << "player" << j << " died! " << endl;
                //if(!map[bombRight.x][bombRight.y].contain_bomb)
                    return i;
            }
            else if(map[bombRight.x][bombRight.y].character_inside[j] && player[j].alive==1 && player[j].item[11] ==1){
                player[j].item[11] = 0;
            }
        }
        if(map[bombRight.x][bombRight.y].contain_bomb){
            //bomb = map[bombRight.x][bombRight.y].bomb->bomb_explode(map[bombRight.x][bombRight.y].bomb->number, bomb);
            return i;
        }
        else if(map[bombRight.x][bombRight.y].wall) {
            if(Mode == 1 &&bombRight.x <=9 && bombRight.x >=6 &bombRight.y >=3 & bombRight.y <= 6){
                boss.boss_life--;
            }
            return i-1;
        }
        else if(map[bombRight.x][bombRight.y].contain_emptybox){
            map[bombRight.x][bombRight.y].collapse();
            return i;
        }
//        else if(map[bombRight.x][bombRight.y].contain_item && map[bombRight.x][bombRight.y].item->destroyed==0){
//            map[bombRight.x][bombRight.y].collapse();
//            return i;
//        }
    }
    return bomb_distance;
}
Bomb** Bomb::bomb_explode(int num, Bomb** _bomb){
    if(owner != -1) player[owner].bomb_left++;
    clk = 0;
    //cout << "bomb " << num << " exploded" << endl;
    //for(int i = 0; i<bomb_num; i++) cout << "before  " << (*_bomb)[i].bomb_loc.x << " " << (*_bomb)[i].bomb_loc.y << "  owner= " << (*_bomb)[i].owner << "  number= " << (*_bomb)[i].number << endl;
    map[bomb_loc.x][bomb_loc.y].contain_bomb = 0;
    map[bomb_loc.x][bomb_loc.y].bomb = NULL;
    bomb_num--;
    Bomb * newpointerbomb = NULL;
    newpointerbomb = new Bomb [bomb_num];
    for(int i = 0; i<num; i++) newpointerbomb[i] = (*_bomb)[i];
    for(int i = num; i<bomb_num; i++) {
        newpointerbomb[i] = (*_bomb)[i+1];
        newpointerbomb[i].number--;
    }
    newpointerbomb = *changemap(&newpointerbomb);
    //for(int i = 0; i<bomb_num; i++) cout << "after change " << newpointerbomb[i].bomb_loc.x << " " << newpointerbomb[i].bomb_loc.y << "  owner= " << newpointerbomb[i].owner << "  number= " << newpointerbomb[i].number << endl;
    //cout << "bomb_num" << bomb_num << endl;
    if(bomb_num==0) newpointerbomb = NULL;
    Bomb * temppointer;
    temppointer = *_bomb;
    *_bomb = newpointerbomb;
    bomb = *_bomb;
    //delete [] temppointer;   //不知道為什麼不能用
    return _bomb;
}
Bomb** Bomb::changemap(Bomb** newpointerbomb){
    int bomb_farest[4];
    bool bomb_on_character = 0;
    for(int i = 0; i<Player_number; i++){
        if(map[bomb_loc.x][bomb_loc.y].character_inside[i] && player[i].alive && player[i].item[11] ==0) {
            bomb_on_character = 1;
            player[i].dead();
            cout << "player" << i << " died!" << endl;
        }
        else if(map[bomb_loc.x][bomb_loc.y].character_inside[i] && player[i].alive && player[i].item[11] ==1){
            bomb_on_character = 1;
            player[i].item[11] = 0;
        }
        bomb_farest[UP] = bomb_farest[DOWN] = bomb_farest[LEFT] = bomb_farest[RIGHT] = 0;
    }
    if(!bomb_on_character){
        bomb_farest[UP] = bomb_up();
        bomb_farest[DOWN] = bomb_down();
        bomb_farest[LEFT] = bomb_left();
        bomb_farest[RIGHT] = bomb_right();
    }
    //cout << bomb_farest[UP] << " " << bomb_farest[DOWN] << " " << bomb_farest[LEFT] << " " << bomb_farest[RIGHT] << endl;
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

    bool bombup=0, bombdown=0, bombleft=0, bombright=0;
    Location locup(bomb_loc.x, bomb_loc.y-bomb_farest[UP]),
            locdown(bomb_loc.x, bomb_loc.y+bomb_farest[DOWN]),
            locleft(bomb_loc.x-bomb_farest[LEFT], bomb_loc.y),
            locright(bomb_loc.x+bomb_farest[RIGHT], bomb_loc.y);

    if(map[bomb_loc.x][bomb_loc.y-bomb_farest[UP]].contain_bomb) bombup = 1;
    if(map[bomb_loc.x][bomb_loc.y+bomb_farest[DOWN]].contain_bomb) bombdown = 1;
    if(map[bomb_loc.x-bomb_farest[LEFT]][bomb_loc.y].contain_bomb) bombleft = 1;
    if(map[bomb_loc.x+bomb_farest[RIGHT]][bomb_loc.y].contain_bomb) bombright = 1;


    if(bombup && map[locup.x][locup.y].contain_bomb)
        *newpointerbomb = *map[locup.x][locup.y].bomb->bomb_explode(map[locup.x][locup.y].bomb->number, newpointerbomb);
    if(bombdown && map[locdown.x][locdown.y].contain_bomb)
        *newpointerbomb = *map[locdown.x][locdown.y].bomb->bomb_explode(map[locdown.x][locdown.y].bomb->number, newpointerbomb);
    if(bombleft && map[locleft.x][locleft.y].contain_bomb)
        *newpointerbomb = *map[locleft.x][locleft.y].bomb->bomb_explode(map[locleft.x][locleft.y].bomb->number, newpointerbomb);
    if(bombright && map[locright.x][locright.y].contain_bomb)
        *newpointerbomb = *map[locright.x][locright.y].bomb->bomb_explode(map[locright.x][locright.y].bomb->number, newpointerbomb);

    //for(int i = 0; i<bomb_num; i++) cout << (*newpointerbomb)[i].bomb_loc.x << " " << (*newpointerbomb)[i].bomb_loc.y << "  owner= " << (*newpointerbomb)[i].owner << "  number= " << (*newpointerbomb)[i].number << endl;

    bomb = *newpointerbomb;

    return newpointerbomb;
}