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
    public:
        Map();
        void collapse(); //bomb爆炸時呼叫
        void met_character(int player); //player呼叫
        void item_taken(int player); //player呼叫
        //感覺map還有很多要寫，只是我對遊戲不熟所以目前想不到
    private:
        Location map_loc;  //add new constructor to initialize map_loc (?
        Bomb bomb;
        bool wall, contain_bomb, contain_item[12];
        Item* item[12]; //constructor initialize //use pointer to enable polymorphism
        bool* character_inside;  //constructor initialize : new [4]
};

#endif

