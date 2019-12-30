#ifndef BOMBEER_MAN_BOMB_H
#define BOMBEER_MAN_BOMB_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Location.h"
#include <ctime>

class Bomb {
    friend class Player;
    public:
        Bomb();
        Bomb(Location, int distance);
        Bomb(const Bomb &copy);        //copy constructor
        Bomb operator=(const Bomb &);
        Location bomb_right();  //determine which map (in which box/player is located) will be bombed
        Location bomb_left();
        Location bomb_up();
        Location bomb_down();
        Bomb* bomb_explode(int, Bomb *);  //player放置bomb後經過一段時間後爆炸
        void changemap(Location);
        clock_t clk;
    private:
        Location bomb_loc;  //player來設定
        int bomb_distance;  //由player放下bomb時設定, 爆炸能炸到的距離 原本是十字 (＝1)

};

#endif
