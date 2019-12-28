#ifndef BOMBEER_MAN_BUTTON_H
#define BOMBEER_MAN_BUTTON_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"

enum ButtonSprite{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
};

class RectButton{
    public:
        RectButton();
        RectButton(SDL_Rect dest);
        void handleEvent(SDL_Event* e);
        void rectrender(bool big=0);
        Texture buttontexture;
        ButtonSprite CurrentSprite;
    private:
        SDL_Rect DestPosition;
};

class CircleButton{
    public:
        CircleButton();
        CircleButton(SDL_Rect dest, SDL_Point center, int r);
        void handleEvent(SDL_Event* e);
        void circlerender(bool big=0);
        Texture buttontexture;
        ButtonSprite CurrentSprite;
    private:
        SDL_Point DestCenter;
        int Button_radius;
        SDL_Rect DestPosition;
};

#endif //BOMBEER_MAN_BUTTON_H
