#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//#include "Player.h"
//#include "Bomb.h"
//#include "Item.h"

class Map {
    friend class Character;
    friend class Bomb;
    friend class Item;
    public:
        void collapse();
        void met_character(int player);
        void item_taken(int player);

    private:
        Map();
        SDL_Point map_loc;
        bool bomb, box, wall;
        int item[12];
        bool *character_inside;
};



