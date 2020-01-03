#ifndef BOMBEER_MAN_PLAYER_H
#define BOMBEER_MAN_PLAYER_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "texture.h"
#include "Item.h"
#include "Location.h"
#include "Bomb.h"

enum Direction{ UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };

class Player {
    friend int main(int, char*args[]);
    friend int quit_restart_home();
    friend int PVE();
    friend int PVP();
    friend void PVE_initialize();
    friend void PVP_initialize();
    friend void PVE_Show_data();
    friend void PVP_Show_data();
public:
    Player();
    Player(int num);
    bool dead();                             //call by class Bomb
    void move(Direction);
    void determine_loc();                    //use player_point to determine player_loc
    void finish_moving();
    void get_item(Item *);
    void useitem(Item *);                    //use pointer to enable polymorphism
    Bomb** putbomb(Bomb **);
    void player_render();
    bool alive;
    Item * item_owned[12];
    bool item[12];
    int score, bomb_distance, bomb_available, bomb_left;
    Location player_loc;
    static int count_rank;
private:
    int player_num, rank, rate;
    Texture picture;
    SDL_Point player_point;
};

#endif
