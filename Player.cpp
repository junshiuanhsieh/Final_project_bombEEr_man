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
Player* player = NULL;

Player::Player(){
    alive = true;
    for(int i = 0; i<Total_item; i++) {
        item[i] = 0;
        item_owned[i] = NULL;
    }
    score = 0;
    bomb_distance = 1;
    bomb_available = 1;
    bomb_left = 1;
}
Player::Player(int num) : player_num(num){
    alive = true;
    for(int i = 0; i<Total_item; i++) {
        item[i] = 0;
        item_owned[i] = NULL;
    }
    score = 0;
    form = character_picture[num];
    bomb_distance = 1;
    bomb_available = 1;
    bomb_left = 1;

//    if(form==0) picture.loadFromFile("../character_image/character0.png");}
//    else if(form==1) picture.loadFromFile("../character_image/character1.png");
//    else if(form==2) picture.loadFromFile("../character_image/character2.png");
//    else if(form==3) picture.loadFromFile("../character_image/character3.png");
//    else if(form==4) picture.loadFromFile("../character_image/character4.png");
}
bool Player::dead(){
    alive = false;
    for(int i = 0; i<Total_item; i++) item_owned[i] = 0;
}
void Player::move(Direction dir, int s){
    if(dir == UP) {
        if(player_point.y >= 105+s) {
            bool change_loc = 0, soon_change_loc = 0;
            if((player_point.y-s-75) / 60 != player_loc.y && player_loc.y>0) change_loc = 1;
            if((player_point.y-30-75) / 60 != player_loc.y && player_loc.y>0) soon_change_loc = 1;
            if(change_loc){
                if(map[player_loc.x][player_loc.y-1].met_character(player_num)){
                    player_point.y -= s;
                    map[player_loc.x][player_loc.y-1].character_inside[player_num] = 1;
                    map[player_loc.x][player_loc.y].character_inside[player_num] = 0;
                    player_loc.y--;
                }
            }
            else if(soon_change_loc){
                if(map[player_loc.x][player_loc.y-1].met_character(player_num)){
                    player_point.y -= s;
                }
            }
            else player_point.y -= s;
        }
    }
    else if(dir == DOWN){
        if(player_point.y <= 705-s) {
            bool change_loc = 0, soon_change_loc = 0;
            if((player_point.y+s-75) / 60 != player_loc.y && player_loc.y<11) change_loc = 1;
            if((player_point.y+30-75) / 60 != player_loc.y && player_loc.y<11) soon_change_loc = 1;
            if(change_loc){
                if(map[player_loc.x][player_loc.y+1].met_character(player_num)){
                    player_point.y += s;
                    map[player_loc.x][player_loc.y+1].character_inside[player_num] = 1;
                    map[player_loc.x][player_loc.y].character_inside[player_num] = 0;
                    player_loc.y++;
                }
            }
            else if(soon_change_loc){
                if(map[player_loc.x][player_loc.y+1].met_character(player_num)){
                    player_point.y += s;
                }
            }
            else player_point.y += s;
        }
    }
    else if(dir == LEFT){
        if(player_point.x >= 50+s) {
            bool change_loc = 0, soon_change_loc = 0;
            if((player_point.x-s-20) / 60 != player_loc.x && player_loc.x>0) change_loc = 1;
            if((player_point.x-30-20) / 60 != player_loc.x && player_loc.x>0) soon_change_loc = 1;
            if(change_loc){
                if(map[player_loc.x-1][player_loc.y].met_character(player_num)){
                    player_point.x -= s;
                    map[player_loc.x-1][player_loc.y].character_inside[player_num] = 1;
                    map[player_loc.x][player_loc.y].character_inside[player_num] = 0;
                    player_loc.x--;
                }
            }
            else if(soon_change_loc){
                if(map[player_loc.x-1][player_loc.y].met_character(player_num)){
                    player_point.x -= s;
                }
            }
            else player_point.x -= s;
        }
    }
    else if(dir == RIGHT){
        if(player_point.x <= 950-s) {
            bool change_loc = 0, soon_change_loc = 0;
            if((player_point.x+s-20) / 60 != player_loc.x && player_loc.x<16) change_loc = 1;
            if((player_point.x+30-20) / 60 != player_loc.x && player_loc.x<16) soon_change_loc = 1;
            if(change_loc){
                if(map[player_loc.x+1][player_loc.y].met_character(player_num)){
                    player_point.x += s;
                    map[player_loc.x+1][player_loc.y].character_inside[player_num] = 1;
                    map[player_loc.x][player_loc.y].character_inside[player_num] = 0;
                    player_loc.x++;
                }
            }
            else if(soon_change_loc){
                if(map[player_loc.x+1][player_loc.y].met_character(player_num)){
                    player_point.x += s;
                }
            }
            else player_point.x += s;
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
Bomb* Player::putbomb(Bomb * bomb){
    bomb_num++;
    Bomb* temp_bomb;
    temp_bomb= new Bomb [bomb_num];
    Bomb* temptempbomb;
    temptempbomb = bomb;
    for(int i = 0; i<bomb_num-1; i++) temp_bomb[i] = Bomb(bomb[i]);
    Bomb newbomb(player_loc,bomb_distance, player_num);
    temp_bomb[bomb_num-1] = Bomb(newbomb);
    bomb = temp_bomb;
    temp_bomb = temptempbomb;
    map[player_loc.x][player_loc.y].contain_bomb = 1;
    map[player_loc.x][player_loc.y].bomb = & bomb[bomb_num-1];
    delete [] temp_bomb;
    return bomb;
}
void Player::get_item(Item * item){
    item_owned[item->item_num]++;
    item->taken_by_player(player_num);
}
void Player::useitem(Item * item){
    item_owned[item->item_num]--;
    item->used();
}
void Player::player_render(){
    SDL_Rect player_dest = {player_point.x-30, player_point.y-30, 60, 60};
    picture.render(&player_dest);
}
