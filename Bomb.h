#ifndef BOMBEER_MAN_BOMB_H
#define BOMBEER_MAN_BOMB_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Map.h"
#include "Item.h"
#include "Player.h"

class Bomb {
    friend class Player;
    public:
        Bomb();
        Bomb(Location, int distance);
        Location bomb_right();  //determine which map (in which box/player is located) will be bombed
        Location bomb_left();
        Location bomb_up();
        Location bomb_down();
        void bomb_explode();  //player放置bomb後經過一段時間後爆炸
        void changemap(Location);

    private:
        Location bomb_loc;  //player來設定
        int bomb_distance;  //由player放下bomb時設定, 爆炸能炸到的距離 原本是十字 (＝1)

};

#endif
