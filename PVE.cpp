#include "PVE.h"
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
bool PVE_quit = 0;
int Choosenumber(){
    int num = 0;
    int TOTAL_NUMBERBUTTON = 3;
    const int BUTTON_NUMBER_WIDTH = 200;
    const int BUTTON_NUMBER_HEIGHT = 100;
    Texture choosenumber;
    RectButton numberbuttons[TOTAL_NUMBERBUTTON];
    SDL_Rect numberbutton_dest[TOTAL_NUMBERBUTTON];
    for(int i = 0; i<TOTAL_NUMBERBUTTON; i++){
        numberbutton_dest[i].x = 300*i+200;
        numberbutton_dest[i].y = 500;
        numberbutton_dest[i].w = BUTTON_NUMBER_WIDTH;
        numberbutton_dest[i].h = BUTTON_NUMBER_HEIGHT;
    }
    for(int i = 0; i<TOTAL_NUMBERBUTTON; i++) numberbuttons[i] = RectButton(numberbutton_dest[i]);
    choosenumber.loadFromFile("../PVE_image/choosenumber_background.png");
    for(int i = 0; i<TOTAL_NUMBERBUTTON; i++) numberbuttons[i].buttontexture.loadFromFile("../PVE_image/choosenumber_button.png");
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    choosenumber.render(NULL);
    SDL_RenderPresent( gRenderer );

    SDL_Event numberevent;
    while(!PVE_quit) {
        while (SDL_PollEvent(&numberevent) != 0) {
            if (numberevent.type == SDL_QUIT) PVE_quit = true;
            for(int i = 0; i < TOTAL_NUMBERBUTTON; i++) numberbuttons[i].handleEvent(&numberevent);
        }
        if (numberevent.type == SDL_QUIT) return 0;
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        choosenumber.render(NULL);
        for(int i = 0; i < TOTAL_NUMBERBUTTON; i++) {
            bool big = 1;
            if(numberbuttons[i].CurrentSprite==BUTTON_SPRITE_MOUSE_OUT) big = 0;
            numberbuttons[i].rectrender(big);
            if(numberbuttons[i].CurrentSprite==BUTTON_SPRITE_MOUSE_UP) {
                num = i+1;
            }
        }
        SDL_RenderPresent( gRenderer );
        if(num != 0) return num;
     }
    return num;
}
void PVE(){
    int number = 0;
    number = Choosenumber();
    cout << number << endl;
    while(!PVE_quit){
        if(number == 1) PVE1(1);
        else if(number == 2) PVE2(2);
        else if(number == 3) PVE3(3);
    }
}

void PVE1(int num){
    Scrolling(num);
}
void PVE2(int num){
    Scrolling(num);
}
void PVE3(int num){
    Scrolling(num);
}

void Scrolling(int num){
    Texture scrolling;
    scrolling.loadFromFile("../PVE_image/scrolling_background.png");
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    scrolling.render(NULL);
    SDL_RenderPresent( gRenderer );

    SDL_Event scrollingevent;
    while(!PVE_quit) {
        while (SDL_PollEvent(&scrollingevent) != 0) {
            if (scrollingevent.type == SDL_QUIT) PVE_quit = true;
        }
        if(num==1){

        }
        else{

        }
    }
}