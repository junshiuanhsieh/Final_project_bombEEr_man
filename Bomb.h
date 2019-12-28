#ifndef BOMBEER_MAN_BOMB_H
#define BOMBEER_MAN_BOMB_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Bomb {
    public:
        Bomb();
        SDL_Point bomb_right();
        SDL_Point bomb_left();
        SDL_Point bomb_up();
        SDL_Point bomb_down();
        void changemap(SDL_Point);

    private:
        SDL_Point bomb_loc;
        int bomb_distance;

};

#endif
