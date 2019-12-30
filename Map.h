#ifndef BOMBEER_MAN_MAP_H
#define BOMBEER_MAN_MAP_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Location.h"
#include "Item.h"
#include "Bomb.h"

class Map {
    friend class Player;
    friend class Bomb;
    friend class Item;
    friend void PVE();
    friend void PVP();
    public:
        Map();
        Map(Location);
        void collapse();                          //bomb爆炸時呼叫
        bool met_character(int player);             //player呼叫 判斷是否能走過去
        int item_taken(int player);              //player呼叫
        bool wall, contain_bomb, contain_emptybox, contain_item;
        void render_map();
        //感覺map還有很多要寫，只是我對遊戲不熟所以目前想不到
    private:
        Location map_loc;                          //add new constructor to initialize map_loc (?
        Bomb* bomb;
        empty_box* emptybox;
        Item* item;                        //constructor initialize //use pointer to enable polymorphism
        int which_item;
        bool* character_inside;               //constructor initialize : new
        Uint8 explode_blending;
};

#endif

