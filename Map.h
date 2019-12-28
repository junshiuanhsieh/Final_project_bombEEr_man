#ifndef BOMBEER_MAN_MAP_H
#define BOMBEER_MAN_MAP_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Player.h"
#include "Bomb.h"
#include "Item.h"
#include "Location.h"

class Map {
    friend class Player;
    friend class Bomb;
    friend class Item;
    public:
        Map();
        void collapse();
        void met_character(int player);
        void item_taken(int player);

    private:
        Location map_loc;
        bool bomb, box, wall, item[12];
        bool* character_inside;
};

#endif

