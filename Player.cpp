#include "Player.h"
#include "Bomb.h"
#include "Map.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Renderer* gRenderer;
extern int* character_picture;
extern const int Total_item = 12;
extern Map** map;
extern Player* player = NULL;

Player::Player(){
    alive = true;
    for(int i = 0; i<Total_item; i++) {
        item[i] = 0;
        item_owned[i] = NULL;
    }
    score = 0;
    bomb_distance = 1;

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
    if(form==0) picture.loadFromFile("../character_image/character0.png");
    if(form==1) picture.loadFromFile("../character_image/character1.png");
    if(form==2) picture.loadFromFile("../character_image/character2.png");
    if(form==3) picture.loadFromFile("../character_image/character3.png");
    if(form==4) picture.loadFromFile("../character_image/character4.png");
}
bool Player::dead(){
    alive = false;
    for(int i = 0; i<Total_item; i++) item_owned[i] = 0;
}
void Player::move(Direction dir, int s){
    if(dir == UP) {
        if(player_point.y > 0) {player_point.y -= s;}
    }
    else if(dir == DOWN){
        if(player_point.y < 600) {player_point.y += s;}
    }
    else if(dir == LEFT){
        if(player_point.x > 0) {player_point.x -= s;}
    }
    else if(dir == RIGHT){
        if(player_point.x < 900) {player_point.x += s;}
    }
    determine_loc();
}
void Player::determine_loc(){
    player_loc.x = (player_point.x-10) / 60;
    player_loc.y = (player_point.y-60) / 60;
}
void Player::get_item(Item * item){
    item_owned[item->item_num]++;
    item->taken_by_player(player_num);
}
void Player::useitem(Item * item){
    item_owned[item->item_num]--;
    item->used();
}
void Player::putbomb(Bomb & newbomb){
    newbomb = Bomb(player_loc, bomb_distance);
}
void Player::player_render(){
    SDL_Rect player_dest = {};
    picture.render(&player_dest);
}


//bool Player::operator! (){
//    return alive;
//}
//Player Player::operator+(int addscore){score += addscore;}
//Player Player::operator-(int minusscore){score -= minusscore;}