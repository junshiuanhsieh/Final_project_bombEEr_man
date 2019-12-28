#ifndef BOMBEER_MAN_PLAYER_H
#define BOMBEER_MAN_PLAYER_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Bomb.h"


class Player {
    public:
        Player();
        Player(int num);
        bool dead();
        void placebomb(int x, int y, Bomb);
        void move(int dir, int s);
        void get_item(int item);
        void useitem(int item_num);
//        bool operator! ();
//        Player operator+(int);
//        Player operator-(int);
        bool alive, item[12];
        int score;
        SDL_Point player_loc;
    private:
        int form;

};

#endif

