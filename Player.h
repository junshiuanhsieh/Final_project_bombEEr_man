#ifndef BOMBEER_MAN_PLAYER_H
#define BOMBEER_MAN_PLAYER_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "texture.h"
#include "Item.h"
#include "Map.h"

enum Direction{ UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };

class Player {
    public:
        Player();
        Player(int num);
        bool dead();
        //void placebomb(int x, int y);
        void move(Direction, int s);
        void determine_loc();
        void get_item(Item &);
        void useitem(Item &);
        void player_render();
        bool alive;
        int item_owned[12];
        int score;
        Location player_loc;
    private:
        int player_num, form, bomb_distance;
        Texture picture;
        SDL_Point player_point;
};


#endif

