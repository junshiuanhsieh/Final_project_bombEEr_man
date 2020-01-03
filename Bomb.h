#ifndef BOMBEER_MAN_BOMB_H
#define BOMBEER_MAN_BOMB_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Location.h"
#include <ctime>


class Bomb {
    friend class Player;
    friend int PVE();
    friend int PVP();
    public:
        Bomb();
        Bomb(Location, int distance, int player_num, int _number);
        Bomb(const Bomb &copy);        //copy constructor
        Bomb operator=(const Bomb &);
        int bomb_right();  //determine which map (in which box/player is located) will be bombed
        int bomb_left();
        int bomb_up();
        int bomb_down();
        Bomb** bomb_explode(int, Bomb**);  //player放置bomb後經過一段時間後爆炸
        Bomb** changemap(Bomb **);
        clock_t clk;
        int number;
    private:
        Location bomb_loc;  //player來設定
        int bomb_distance, owner;  //由player放下bomb時設定, 爆炸能炸到的距離 原本是十字 (＝1)

};

#endif
