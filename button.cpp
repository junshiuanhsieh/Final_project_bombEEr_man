#include "button.h"
#include <cmath>

RectButton::RectButton(){}
CircleButton::CircleButton(){}

RectButton::RectButton(SDL_Rect dest) :DestPosition(dest){
    CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}
CircleButton::CircleButton(SDL_Rect dest, SDL_Point center, int r) :DestPosition(dest), DestCenter(center), Button_radius(r){
    CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void RectButton::handleEvent(SDL_Event* e){
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
        int x, y;
        SDL_GetMouseState( &x, &y );
        bool inside = true;
        if( x < DestPosition.x ) inside = false;
        else if( x > DestPosition.x + DestPosition.w ) inside = false;
        else if( y < DestPosition.y ) inside = false;
        else if( y > DestPosition.y + DestPosition.h ) inside = false;
        if(!inside ) CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        else{
            switch( e->type ){
                case SDL_MOUSEMOTION:
                    CurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    CurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;
                case SDL_MOUSEBUTTONUP:
                    CurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        }
    }
}
void CircleButton::handleEvent(SDL_Event* e){
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
        int x, y;
        SDL_GetMouseState( &x, &y );
        bool inside = true;
        if(sqrt(pow(x-DestCenter.x,2)+pow(y-DestCenter.y,2)) > Button_radius) inside = false;
        if(!inside ) CurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        else{
            switch(e->type){
                case SDL_MOUSEMOTION:
                    CurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    CurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;
                case SDL_MOUSEBUTTONUP:
                    CurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        }
    }
}

void RectButton::rectrender(bool big){
    buttontexture.render(&DestPosition, NULL, big);
}
void CircleButton::circlerender(bool big){
    if(!big) buttontexture.render(&DestPosition, NULL);
    else{
        SDL_Rect newdest;
        newdest.x = DestPosition.x - ((DestCenter.x-DestPosition.x)/10);
        newdest.y = DestPosition.y - ((DestCenter.y-DestPosition.y)/10);
        newdest.w = DestPosition.w + ((DestCenter.x-DestPosition.x)/10) + ((DestPosition.x+DestPosition.w-DestCenter.x)/10);
        newdest.h = DestPosition.h + ((DestCenter.y-DestPosition.y)/10) + ((DestPosition.y+DestPosition.h-DestCenter.y)/10);;
        buttontexture.render(&newdest, NULL);
    }
}


