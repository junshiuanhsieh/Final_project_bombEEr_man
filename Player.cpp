#include "Player.h"

extern const int SCREEN_WIDTH = 1200;
extern const int SCREEN_HEIGHT = 750;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern bool quit;
extern int Player_number, Mode;
extern int* character_picture;
extern const int Total_item;


Player::Player(){
    alive = true;
    for(int i = 0; i<Total_item; i++) item[i] = 0;
    score = 0;
}
Player::Player(int num){
    alive = true;
    for(int i = 0; i<Total_item; i++) item[i] = 0;
    score = 0;
    form = character_picture[num];
}
bool Player::dead(){
    alive = false;
}
void Player::placebomb(int x, int y, Bomb newbomb){

}
void Player::move(int dir, int s){

}
void Player::get_item(int item){

}
void Player::useitem(int item_num){

}
//bool Player::operator! (){
//    return alive;
//}
//Player Player::operator+(int addscore){score += addscore;}
//Player Player::operator-(int minusscore){score -= minusscore;}