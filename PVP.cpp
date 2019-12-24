#include "PVP.h"
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern bool quit;

void PVP(int number){
    cout << number << endl;
    if(number == 1) PVP1(1);
    else if(number == 2) PVP2(2);
    else if(number == 3) PVP3(3);
}

void PVP1(int number){
    PVPScrolling(number);
}
void PVP2(int number){
    PVPScrolling(number);
}
void PVP3(int number){
    PVPScrolling(number);
}

void PVPScrolling(int number){
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

