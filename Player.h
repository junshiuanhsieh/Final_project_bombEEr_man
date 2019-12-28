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
    public:
        Player();
        Player(int num);
        bool dead();                             //call by class Bomb
        void move(Direction, int s);
        void determine_loc();                    //use player_point to determine player_loc
        void get_item(Item *);
        void useitem(Item *);                    //use pointer to enable polymorphism
        void putbomb(Bomb &);
        void player_render();
        bool alive;
        Item * item_owned[12];
        bool item[12];
        int score;
        Location player_loc;
    private:
        int player_num, form, bomb_distance;
        Texture picture;
        SDL_Point player_point;
};


#endif

