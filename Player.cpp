#include "Player.h"
#include "Bomb.h"
#include "Map.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Renderer* gRenderer;
extern int* character_picture;
extern const int Total_item = 12;
extern Map** map;
extern int bomb_num;
extern int Player_number;
extern Bomb * bomb;

Player::Player(){
    alive = true;
    for(int i = 0; i<Total_item; i++) {
        item[i] = 0;
        item_owned[i] = NULL;
    }
    score = 0;
    rank = 1;
    bomb_distance = 1;
    bomb_available = 1;
    bomb_left = 1;
    rate = 7;
    player_num = -1;
}
Player::Player(int num) : player_num(num){
    alive = true;
    for(int i = 0; i<Total_item; i++) {
        item[i] = 0;
        item_owned[i] = NULL;
    }
    score = 0;
    rank = 1;
    bomb_distance = 1;
    bomb_available = 1;
    bomb_left = 1;
    rate = 7;
}
int Player::count_rank = Player_number;
bool Player::dead(){
    alive = false;
    for(int i = 0; i<Total_item; i++) item_owned[i] = 0;
    rank = count_rank;
}
void Player::move(Direction dir){
    if(this->item[5] == 1){
        if(dir == UP) dir =DOWN;
        else if(dir == DOWN) dir =UP;
        else if(dir == LEFT) dir =RIGHT;
        else dir = LEFT;
    }
    if(dir == UP) {
        if(player_point.y >= 105+rate) {
            if(map[player_loc.x][player_loc.y].contain_item ==1 ){
                get_item(map[player_loc.x][player_loc.y].item);
                map[player_loc.x][player_loc.y].item_taken(this->player_num);
            }

            bool change_loc = 0, soon_change_loc = 0;
            if((player_point.y-rate-75) / 60 != player_loc.y && player_loc.y>0) change_loc = 1;
            if((player_point.y-30-75) / 60 != player_loc.y && player_loc.y>0) soon_change_loc = 1;
            if(change_loc){
                if(map[player_loc.x][player_loc.y-1].met_character(player_num)){
                    player_point.y -= rate;
                    map[player_loc.x][player_loc.y-1].character_inside[player_num] = 1;
                    map[player_loc.x][player_loc.y].character_inside[player_num] = 0;
                    player_loc.y--;
                }
            }
            else if(soon_change_loc){
                if(map[player_loc.x][player_loc.y-1].met_character(player_num)){
                    player_point.y -= rate;
                }
            }
            else player_point.y -= rate;
        }
    }
    else if(dir == DOWN){
        if(player_point.y <= 705-rate) {
            if(map[player_loc.x][player_loc.y].contain_item ==1 ){
                get_item(map[player_loc.x][player_loc.y].item);
                map[player_loc.x][player_loc.y].item_taken(this->player_num);
            }

            bool change_loc = 0, soon_change_loc = 0;
            if((player_point.y+rate-75) / 60 != player_loc.y && player_loc.y<11) change_loc = 1;
            if((player_point.y+30-75) / 60 != player_loc.y && player_loc.y<11) soon_change_loc = 1;
            if(change_loc){
                if(map[player_loc.x][player_loc.y+1].met_character(player_num)){
                    player_point.y += rate;
                    map[player_loc.x][player_loc.y+1].character_inside[player_num] = 1;
                    map[player_loc.x][player_loc.y].character_inside[player_num] = 0;
                    player_loc.y++;
                }
            }
            else if(soon_change_loc){
                if(map[player_loc.x][player_loc.y+1].met_character(player_num)){
                    player_point.y += rate;
                }
            }
            else player_point.y += rate;
        }
    }
    else if(dir == LEFT){
        if(player_point.x >= 50+rate) {
            if(map[player_loc.x][player_loc.y].contain_item ==1 ){
                get_item(map[player_loc.x][player_loc.y].item);
                map[player_loc.x][player_loc.y].item_taken(this->player_num);
            }
            bool change_loc = 0, soon_change_loc = 0;
            if((player_point.x-rate-20) / 60 != player_loc.x && player_loc.x>0) change_loc = 1;
            if((player_point.x-30-20) / 60 != player_loc.x && player_loc.x>0) soon_change_loc = 1;
            if(change_loc){
                if(map[player_loc.x-1][player_loc.y].met_character(player_num)){
                    player_point.x -= rate;
                    map[player_loc.x-1][player_loc.y].character_inside[player_num] = 1;
                    map[player_loc.x][player_loc.y].character_inside[player_num] = 0;
                    player_loc.x--;
                }
            }
            else if(soon_change_loc){
                if(map[player_loc.x-1][player_loc.y].met_character(player_num)){
                    player_point.x -= rate;
                }
            }
            else player_point.x -= rate;
        }
    }
    else if(dir == RIGHT){
        if(player_point.x <= 950-rate) {
            if(map[player_loc.x][player_loc.y].contain_item ==1 ){
                get_item(map[player_loc.x][player_loc.y].item);
                map[player_loc.x][player_loc.y].item_taken(this->player_num);
            }
            bool change_loc = 0, soon_change_loc = 0;
            if((player_point.x+rate-20) / 60 != player_loc.x && player_loc.x<16) change_loc = 1;
            if((player_point.x+30-20) / 60 != player_loc.x && player_loc.x<16) soon_change_loc = 1;
            if(change_loc){
                if(map[player_loc.x+1][player_loc.y].met_character(player_num)){
                    player_point.x += rate;
                    map[player_loc.x+1][player_loc.y].character_inside[player_num] = 1;
                    map[player_loc.x][player_loc.y].character_inside[player_num] = 0;
                    player_loc.x++;
                }
            }
            else if(soon_change_loc){
                if(map[player_loc.x+1][player_loc.y].met_character(player_num)){
                    player_point.x += rate;
                }
            }
            else player_point.x += rate;
        }
    }
    determine_loc();



}
void Player::determine_loc(){
    player_loc.x = (player_point.x-20) / 60;
    player_loc.y = (player_point.y-75) / 60;
}
void Player::finish_moving(){
    player_point.x = 50 + player_loc.x*60;
    player_point.y = 105 + player_loc.y*60;
}
Bomb** Player::putbomb(Bomb ** _bomb){
    //cout << "player " << player_num << " put bomb " << bomb_num << endl;
    bomb_num++;
    Bomb newbomb(player_loc,bomb_distance, player_num, bomb_num-1);
    if(*_bomb == NULL){
        *_bomb = new Bomb ();
        (*_bomb)[0] = newbomb;
        //cout << "first bomb" << (*_bomb)[0].number << endl;
    }
    else {
        Bomb * newbombpointer = NULL,  * temppointer = NULL;
        temppointer = *_bomb;
        newbombpointer = new Bomb [bomb_num];
        for(int i = 0; i<bomb_num-1; i++) newbombpointer[i] = (*_bomb)[i];
        newbombpointer[bomb_num-1] = newbomb;
        *_bomb = newbombpointer;
        delete [] temppointer;
    }
    map[player_loc.x][player_loc.y].contain_bomb = 1;
    map[player_loc.x][player_loc.y].bomb = _bomb[bomb_num-1];
    //for(int i = 0; i<bomb_num; i++) cout << "put bomb " << (*_bomb)[i].bomb_loc.x << " " << (*_bomb)[i].bomb_loc.y << "  owner= " << (*_bomb)[i].owner << endl;
    bomb = *_bomb;
    return _bomb;
}
void Player::get_item(Item * item_get){
    if(item_get->item_num == 5 && item[5] == 1) item[5] = 0;
    else item[item_get->item_num] = 1 ;

    if(item_get->item_num == 0) {
        this->bomb_available++;
        this->bomb_left++;
    }
        //增加一格爆炸範圍
    else if(item_get->item_num == 1){
        this->bomb_distance ++;
    }
        //爆炸威力加到最大
    else if(item_get->item_num == 2){
        this->bomb_distance = 15;
    }
        //走路速度變快
    else if(item_get->item_num == 3){
        this->rate += 2;
    }
        //走路速度變慢
    else if(item_get->item_num == 4){
        this->rate -= 1;
    }
        //逆向寫在move裡面
    else if(item_get->item_num == 5){

    }
        //盾牌直接寫在bomb裡面
    else if(item_get->item_num == 11){

    }

    item_get->taken_by_player(player_num);


}
void Player::useitem(Item * item){
    item_owned[item->item_num]--;
    item->used();
}
void Player::player_render(){
    SDL_Rect player_dest = {player_point.x-30, player_point.y-30, 60, 60};
    picture.render(&player_dest);
}

void Boss::player_render(){

    SDL_Rect boss_dest;

    boss_dest.x = 20 + 60 * 6;
    boss_dest.y = 75 + 60 * 3;
    boss_dest.w = 240;
    boss_dest.h = 240;
    picture.render(&boss_dest);
}