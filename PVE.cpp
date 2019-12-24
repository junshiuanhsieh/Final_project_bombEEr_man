#include "PVE.h"
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern bool quit;

void PVE(int number){
    cout << number << endl;
    if(number == 1) PVE1(1);
    else if(number == 2) PVE2(2);
    else if(number == 3) PVE3(3);
}

void PVE1(int number){
    PVEScrolling(number);
}
void PVE2(int number){
    PVEScrolling(number);
}
void PVE3(int number){
    PVEScrolling(number);
}

void PVEScrolling(int number){
    Texture scrolling, TextTexture;
    scrolling.loadFromFile("../PVE_image/scrolling_background.png");
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    scrolling.render(NULL);
    SDL_RenderPresent( gRenderer );

    SDL_Event scrollingevent;

    while(!quit) {
        while (SDL_PollEvent(&scrollingevent) != 0) {
            if (scrollingevent.type == SDL_QUIT) quit = true;
        }
        if(number==1){

        }
        else{

        }
    }
}