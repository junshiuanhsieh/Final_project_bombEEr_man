#include "PVP.h"
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern bool quit;
extern int Player_number;

void PVP(){
    if(Player_number == 1) PVP1();
    else if(Player_number == 2) PVP2();
    else if(Player_number == 3) PVP3();

}

void PVP1(){
}
void PVP2(){
}
void PVP3(){
}

//void PVPScrolling(int number){
//    Texture scrolling, TextTexture;
//    scrolling.loadFromFile("../PVP_image/scrolling_background.png");
//    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//    SDL_RenderClear(gRenderer);
//    scrolling.render(NULL);
//    SDL_RenderPresent( gRenderer );
//
//    SDL_Event scrollingevent;
//
//    while(!quit) {
//        while (SDL_PollEvent(&scrollingevent) != 0) {
//            if (scrollingevent.type == SDL_QUIT) quit = true;
//        }
//        if(number==1){
//
//        }
//        else{
//
//        }
//    }
//}

