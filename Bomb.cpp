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
            if(Mode == 1) boss.boss_life --;
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
            if(Mode == 1) boss.boss_life --;
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
            if(Mode == 1) boss.boss_life --;
            return i-1;
        }
        else if(map[bombLeft.x][bombLeft.y].contain_emptybox){
            map[bombLeft.x][bombLeft.y].collapse();
            return i;
        }
//        else if(map[bombLeft.x][bombLeft.y].contai/n_item && map[bombLeft.x][bombLeft.y].item->destroyed==0){
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
                if(Mode == 1) boss.boss_life --;
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
Bomb* Bomb::bomb_explode(int num, Bomb* _bomb){
    //cout << "bomb " << num << " exploded" << endl;
    //for(int i = 0; i<bomb_num; i++) cout << _bomb[i].bomb_loc.x << " " << _bomb[i].bomb_loc.y << endl;
    bomb = _bomb;
    clk = 0;
    bomb_num--;
    Bomb* temp_bomb;
    temp_bomb= new Bomb [bomb_num];
    Bomb* temptempbomb;
    temptempbomb = bomb;
    for(int i = 0; i<num; i++) temp_bomb[i] = (bomb)[i];
    for(int i = num; i<bomb_num; i++) {
        temp_bomb[i] = bomb[i+1];
        temp_bomb[i].number--;
    }
    bomb = temp_bomb;
    temp_bomb = temptempbomb;
    map[bomb_loc.x][bomb_loc.y].contain_bomb = 0;
    map[bomb_loc.x][bomb_loc.y].bomb = NULL;
    player[owner].bomb_left++;
    delete [] temp_bomb;
    changemap();
    return bomb;
}
void Bomb::changemap(){
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

    //呼叫其他bomb.explode的時候this->bomb_loc會被改掉，不知道為什麼，所以先用其他變數存著
    bool bombup=0, bombdown=0, bombleft=0, bombright=0;
    Location locup(bomb_loc.x, bomb_loc.y-bomb_farest[UP]),
            locdown(bomb_loc.x, bomb_loc.y+bomb_farest[DOWN]),
            locleft(bomb_loc.x-bomb_farest[LEFT], bomb_loc.y),
            locright(bomb_loc.x+bomb_farest[RIGHT], bomb_loc.y);

    if(map[bomb_loc.x][bomb_loc.y-bomb_farest[UP]].contain_bomb) bombup = 1;
    if(map[bomb_loc.x][bomb_loc.y+bomb_farest[DOWN]].contain_bomb) bombdown = 1;
    if(map[bomb_loc.x-bomb_farest[LEFT]][bomb_loc.y].contain_bomb) bombleft = 1;
    if(map[bomb_loc.x+bomb_farest[RIGHT]][bomb_loc.y].contain_bomb) bombright = 1;

    if(bombup)
        bomb = map[locup.x][locup.y].bomb->bomb_explode(map[locup.x][locup.y].bomb->number, bomb);
    if(bombdown)
        bomb = map[locdown.x][locdown.y].bomb->bomb_explode(map[locdown.x][locdown.y].bomb->number, bomb);
    if(bombleft)
        bomb = map[locleft.x][locleft.y].bomb->bomb_explode(map[locleft.x][locleft.y].bomb->number, bomb);
    if(bombright)
        bomb = map[locright.x][locright.y].bomb->bomb_explode(map[locright.x][locright.y].bomb->number, bomb);

//    cout << "test up " << bomb_farest[UP] << " " << bomb_loc.x << " " << bomb_loc.y << endl;
//    if(map[bomb_loc.x][bomb_loc.y-bomb_farest[UP]].contain_bomb)
//        bomb = map[bomb_loc.x][bomb_loc.y-bomb_farest[UP]].bomb->bomb_explode(map[bomb_loc.x][bomb_loc.y-bomb_farest[UP]].bomb->number, bomb);
//    cout << "test down " << bomb_farest[DOWN] << " " << bomb_loc.x << " " << bomb_loc.y << endl;
//    if(map[bomb_loc.x][bomb_loc.y+bomb_farest[DOWN]].contain_bomb)
//        bomb = map[bomb_loc.x][bomb_loc.y+bomb_farest[DOWN]].bomb->bomb_explode(map[bomb_loc.x][bomb_loc.y+bomb_farest[DOWN]].bomb->number, bomb);
//    cout << "test left " << bomb_farest[LEFT] << " " << bomb_loc.x << " " << bomb_loc.y << endl;
//    if(map[bomb_loc.x-bomb_farest[LEFT]][bomb_loc.y].contain_bomb)
//        bomb = map[bomb_loc.x-bomb_farest[LEFT]][bomb_loc.y].bomb->bomb_explode(map[bomb_loc.x-bomb_farest[LEFT]][bomb_loc.y].bomb->number, bomb);
//    cout << "test right " << bomb_farest[RIGHT] << " " << bomb_loc.x << " " << bomb_loc.y << endl;
//    if(map[bomb_loc.x+bomb_farest[RIGHT]][bomb_loc.y].contain_bomb)
//        bomb = map[bomb_loc.x+bomb_farest[RIGHT]][bomb_loc.y].bomb->bomb_explode(map[bomb_loc.x+bomb_farest[RIGHT]][bomb_loc.y].bomb->number, bomb);
//    cout << "test finish " << bomb_loc.x << " " << bomb_loc.y << endl;

}
