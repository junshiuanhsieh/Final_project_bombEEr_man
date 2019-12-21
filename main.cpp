#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <cmath>
#include "button.h"
#include "texture.h"
using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 750;
const int TOTAL_MODEBUTTON = 2;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Texture startgame, choosemode;
CircleButton startbomb;
RectButton modebuttons[TOTAL_MODEBUTTON];

void init() {
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
}
void loadMedia(){
    startgame.loadFromFile("../start_image/startbackground.png");
    choosemode.loadFromFile("../start_image/modebackground.png");
    const int BUTTON_START_RADIUS = 180;
    const int BUTTON_MODE_WIDTH = 300;
    const int BUTTON_MODE_HEIGHT = 150;
    SDL_Point startbuttoncenter = {600, 520};
    SDL_Rect startbuttondest = {420,190 , 360, 512};
    startbomb = CircleButton(startbuttondest, startbuttoncenter, BUTTON_START_RADIUS);
    SDL_Rect modebutton_dest[TOTAL_MODEBUTTON];
    for(int i = 0; i<TOTAL_MODEBUTTON; i++){
        modebutton_dest[i].x = 500*i+200;
        modebutton_dest[i].y = 500;
        modebutton_dest[i].w = BUTTON_MODE_WIDTH;
        modebutton_dest[i].h = BUTTON_MODE_HEIGHT;
    }
    for(int i = 0; i<TOTAL_MODEBUTTON; i++) modebuttons[i] = RectButton(modebutton_dest[i]);
    startbomb.buttontexture.loadFromFile("../start_image/startbomb.png");
    for(int i = 0; i<TOTAL_MODEBUTTON; i++) modebuttons[i].buttontexture.loadFromFile("../start_image/modebutton.png");
}
void close(){
    startgame.free();
    choosemode.free();
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] ){
    init();
    loadMedia();
    bool quit = false;
    SDL_Event startevent, modeevent;
    while(!quit){
        while(1){
            while(SDL_PollEvent(&startevent) != 0){
                if(startevent.type == SDL_QUIT) quit = true;
                startbomb.handleEvent(&startevent);
            }
            if(startevent.type == SDL_QUIT) break;
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            startgame.render(NULL);
            bool big = 1;
            if(startbomb.CurrentSprite==BUTTON_SPRITE_MOUSE_OUT) big = 0;
            startbomb.circlerender(big);
            SDL_RenderPresent(gRenderer);
            if(startbomb.CurrentSprite == BUTTON_SPRITE_MOUSE_UP) break;
        }
        if(quit) break;
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        choosemode.render(NULL);
        SDL_RenderPresent( gRenderer );

        while(1){
            while(SDL_PollEvent(&modeevent) != 0){
                if(modeevent.type == SDL_QUIT) quit = true;
                for(int i = 0; i < TOTAL_MODEBUTTON; i++) modebuttons[i].handleEvent(&modeevent);
            }
            if(modeevent.type == SDL_QUIT) break;
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            choosemode.render(NULL);
            for(int i = 0; i < TOTAL_MODEBUTTON; i++) {
                bool big = 1;
                if(modebuttons[i].CurrentSprite==BUTTON_SPRITE_MOUSE_OUT) big = 0;
                modebuttons[i].rectrender(big);
            }
            SDL_RenderPresent( gRenderer );
        }
        if(quit) break;
    }
    close();
    return 0;
}