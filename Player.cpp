#include "Player.h"

extern const int SCREEN_WIDTH = 1200;
extern const int SCREEN_HEIGHT = 750;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern bool quit;
extern int Player_number, Mode;
extern int* character_picture;

Player::Player(int num){
    alive = true;
    for(int i = 0; i<12; i++) item[i] = 0;
    score = 0;
    form =
}
void Player::changescore(int x){

}
bool Player::dead(){

}
void Player::placebomb(int x, int y){

}
void Player::move(int dir, int s){

}
void Player::get_item(int item){

}
void Player::useitem(int item_num){

}