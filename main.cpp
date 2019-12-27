#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <cmath>
#include "button.h"
#include "texture.h"
#include "PVE.h"
#include "PVP.h"
using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 750;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
bool quit;
int Player_number = 0, Mode = 0;
int* character_picture = NULL;

void init();
void close();
void Start();
void Choosemode();
void Choosenumber();
void Scrolling();
void Choosecharacter();
void Tutorial_start();
void Tutorial();

int main( int argc, char* args[] ){
    init();
    quit = false;
    Start();
    if(quit) return 0;
    Choosemode();
    if(quit) return 0;

    if(Mode == 1) PVE();
    else if(Mode == 2) PVP();
    close();
    return 0;
}

void init() {
    if( SDL_Init(SDL_INIT_VIDEO) < 0 ) printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    gWindow = SDL_CreateWindow("bombEEr_man", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
}
void close(){
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}
void Start(){
    CircleButton startbomb;
    Texture startgame;
    const int BUTTON_START_RADIUS = 180;
    SDL_Point startbuttoncenter = {600, 520};
    SDL_Rect startbuttondest={420,190 , 360, 512};
    startbomb = CircleButton(startbuttondest, startbuttoncenter, BUTTON_START_RADIUS);
    startgame.loadFromFile("../start_image/startbackground.png");
    startbomb.buttontexture.loadFromFile("../start_image/startbomb.png");

    SDL_Event startevent;
    while(!quit){
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
}
void Choosemode(){
    RectButton modebuttons[2];
    Texture choosemode;
    const int BUTTON_MODE_WIDTH = 300;
    const int BUTTON_MODE_HEIGHT = 150;
    SDL_Rect modebutton_dest[2];
    for(int i = 0; i<2; i++){
        modebutton_dest[i].x = 500*i+200;
        modebutton_dest[i].y = 500;
        modebutton_dest[i].w = BUTTON_MODE_WIDTH;
        modebutton_dest[i].h = BUTTON_MODE_HEIGHT;
    }
    for(int i = 0; i<2; i++) modebuttons[i] = RectButton(modebutton_dest[i]);
    modebuttons[0].buttontexture.loadFromFile("../start_image/PVEbutton.png");
    modebuttons[1].buttontexture.loadFromFile("../start_image/PVPbutton.png");
    choosemode.loadFromFile("../start_image/modebackground.png");
    SDL_Event modeevent;
    while(!quit){
        while(SDL_PollEvent(&modeevent) != 0){
            if(modeevent.type == SDL_QUIT) quit = true;
            for(int i = 0; i < 2; i++) modebuttons[i].handleEvent(&modeevent);
        }
        if(modeevent.type == SDL_QUIT) return;
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        choosemode.render(NULL);
        for(int i = 0; i < 2; i++) {
            bool big = 1;
            if(modebuttons[i].CurrentSprite==BUTTON_SPRITE_MOUSE_OUT) big = 0;
            modebuttons[i].rectrender(big);
        }
        SDL_RenderPresent( gRenderer );

        if(modebuttons[0].CurrentSprite==BUTTON_SPRITE_MOUSE_UP) {
            Mode = 1;
            cout << "PVE" << endl;
            Choosenumber();
            break;
        }
        if(modebuttons[1].CurrentSprite==BUTTON_SPRITE_MOUSE_UP) {
            Mode = 2;
            cout << "PVP" << endl;
            Choosenumber();
            break;
        }
    }
}
void Choosenumber(){
    int TOTAL_NUMBERBUTTON = 3;
    const int BUTTON_NUMBER_WIDTH = 200;
    const int BUTTON_NUMBER_HEIGHT = 100;
    Texture choosenumber;
    RectButton numberbuttons[TOTAL_NUMBERBUTTON], backto_choosemode;
    SDL_Rect numberbutton_dest[TOTAL_NUMBERBUTTON], backbuttondest={900, 600, 200, 100};
    for(int i = 0; i<TOTAL_NUMBERBUTTON; i++){
        numberbutton_dest[i].x = 300*i+200;
        numberbutton_dest[i].y = 450;
        numberbutton_dest[i].w = BUTTON_NUMBER_WIDTH;
        numberbutton_dest[i].h = BUTTON_NUMBER_HEIGHT;
        numberbuttons[i] = RectButton(numberbutton_dest[i]);
    }
    backto_choosemode = RectButton(backbuttondest);
    choosenumber.loadFromFile("../start_image/choosenumber_background.png");
    backto_choosemode.buttontexture.loadFromFile("../start_image/back.png");
    numberbuttons[0].buttontexture.loadFromFile("../start_image/choosenumber_button1.png");
    numberbuttons[1].buttontexture.loadFromFile("../start_image/choosenumber_button2.png");
    numberbuttons[2].buttontexture.loadFromFile("../start_image/choosenumber_button3.png");

    SDL_Event numberevent;
    while(!quit) {
        while (SDL_PollEvent(&numberevent) != 0) {
            if (numberevent.type == SDL_QUIT) quit = true;
            for(int i = 0; i < TOTAL_NUMBERBUTTON; i++) numberbuttons[i].handleEvent(&numberevent);
            backto_choosemode.handleEvent(&numberevent);
        }
        if (numberevent.type == SDL_QUIT) return;
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        choosenumber.render(NULL);
        for(int i = 0; i < TOTAL_NUMBERBUTTON; i++) {
            bool big = 1;
            if(numberbuttons[i].CurrentSprite==BUTTON_SPRITE_MOUSE_OUT) big = 0;
            numberbuttons[i].rectrender(big);
            if(numberbuttons[i].CurrentSprite==BUTTON_SPRITE_MOUSE_UP) {
                Player_number = i+1;
                cout << "Total player = " << Player_number << endl;
                Choosecharacter();
                return;
            }
        }
        bool backbig = 1;
        if(backto_choosemode.CurrentSprite==BUTTON_SPRITE_MOUSE_OUT) backbig = 0;
        backto_choosemode.rectrender(backbig);
        SDL_RenderPresent(gRenderer);

        if(backto_choosemode.CurrentSprite==BUTTON_SPRITE_MOUSE_UP) {
            Choosemode();
            return;
        }
    }
}
void Scrolling(){}
void Choosecharacter(){
    character_picture = new int[Player_number];
    for(int i = 0; i< Player_number; i++) character_picture[i] = -1;
    int TOTAL_CHARACTER_OPTION = 5;
    Texture choosecharacter;
    RectButton characteroption[TOTAL_CHARACTER_OPTION], backto_number;
    SDL_Rect characteroption_dest[TOTAL_CHARACTER_OPTION], frame[TOTAL_CHARACTER_OPTION], backbuttondest={900, 600, 200, 100};;
    for (int i = 0; i < TOTAL_CHARACTER_OPTION; i++) {
        characteroption_dest[i].x = 125 + i * 200;
        characteroption_dest[i].y = 300;
        characteroption_dest[i].w = 150;
        characteroption_dest[i].h = 150;
        frame[i].x = characteroption_dest[i].x - 10;
        frame[i].y = 290;
        frame[i].w = 170;
        frame[i].h = 170;
        characteroption[i] = RectButton(characteroption_dest[i]);
    }
    backto_number = RectButton(backbuttondest);
    characteroption[0].buttontexture.loadFromFile("../character_image/character0.png");
    characteroption[1].buttontexture.loadFromFile("../character_image/character1.png");
    characteroption[2].buttontexture.loadFromFile("../character_image/character2.png");
    characteroption[3].buttontexture.loadFromFile("../character_image/character3.png");
    characteroption[4].buttontexture.loadFromFile("../character_image/character4.png");
    choosecharacter.loadFromFile("../start_image/choosecharacter_background.png");
    backto_number.buttontexture.loadFromFile("../start_image/back.png");

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    choosecharacter.render(NULL);
    SDL_RenderPresent(gRenderer);

    SDL_Event chooseevent;
    bool choosen[TOTAL_CHARACTER_OPTION], nextplayer;
    for (int i = 0; i < TOTAL_CHARACTER_OPTION; i++) choosen[i] = 0;
    int start_choose, tempchoose, end_choose;

    for(int i = 0; i < Player_number; i++) {
        nextplayer = 0;
        start_choose = 0;
        end_choose = 4;
        while (choosen[start_choose] == 1) start_choose++;
        while (choosen[end_choose] == 1) end_choose--;
        tempchoose = start_choose;
        int big;
        while (!quit) {
            while (SDL_PollEvent(&chooseevent) != 0) {
                backto_number.handleEvent(&chooseevent);
                if (chooseevent.type == SDL_QUIT) {quit = true; return;}
                else if(chooseevent.type == SDL_KEYDOWN) {
                    while(chooseevent.type != SDL_KEYUP) {
                        SDL_PollEvent(&chooseevent);
                        if (chooseevent.type == SDL_QUIT) {quit=true; return;}
                    }
                    if (chooseevent.key.keysym.sym==SDLK_RIGHT || chooseevent.key.keysym.sym==SDLK_d || chooseevent.key.keysym.sym==SDLK_l) {
                        if (tempchoose < end_choose) {
                            tempchoose++;
                            while (choosen[tempchoose] == 1) tempchoose++;
                        }
                    }
                    else if (chooseevent.key.keysym.sym==SDLK_LEFT || chooseevent.key.keysym.sym==SDLK_a || chooseevent.key.keysym.sym==SDLK_j) {
                        if (tempchoose > start_choose) {
                            tempchoose--;
                            while (choosen[tempchoose] == 1) tempchoose--;
                        }
                    }
                    else if (chooseevent.key.keysym.sym==SDLK_RETURN || chooseevent.key.keysym.sym==SDLK_SPACE || chooseevent.key.keysym.sym==SDLK_TAB) {
                        character_picture[i] = tempchoose;
                        choosen[tempchoose] = 1;
                        tempchoose = 0;
                        while (choosen[tempchoose] == 1) tempchoose++;
                        nextplayer = 1;
                    }
                }
                //else if(backto_number.CurrentSprite == BUTTON_SPRITE_MOUSE_OUT) big = 0;

                else if(backto_number.CurrentSprite == BUTTON_SPRITE_MOUSE_UP){
                    Choosenumber();
                    return;
                }
            }
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            choosecharacter.render(NULL);
            big = 1;
            if(backto_number.CurrentSprite == BUTTON_SPRITE_MOUSE_OUT) big = 0;
            backto_number.rectrender(big);
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
            if(character_picture[Player_number-1] == -1) SDL_RenderFillRect(gRenderer, &frame[tempchoose]);
            for (int j = 0; j<TOTAL_CHARACTER_OPTION; j++) {
                if (choosen[j] == 1) {
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
                    SDL_RenderFillRect(gRenderer, &frame[j]);
                }
                characteroption[j].rectrender();
            }
            SDL_RenderPresent(gRenderer);
            if(nextplayer) break;
        }
        cout << "character[" << i << "] = " << character_picture[i] << endl;
        SDL_Delay(400);
    }
    Tutorial_start();
}
void Tutorial_start(){
    SDL_Rect tutorial_dest = {100, 600, 200, 100}, startgame_dest = {450, 400, 300, 300}, back_dest = {900, 600, 200, 100};
    SDL_Point startgame_center = {600, 550};
    Texture tutorial_start;
    RectButton tutorial(tutorial_dest), backto_character(back_dest);
    CircleButton start_game(startgame_dest, startgame_center, 150);
    tutorial_start.loadFromFile("../start_image/tutorial_start_background.png");
    backto_character.buttontexture.loadFromFile("../start_image/back.png");
    tutorial.buttontexture.loadFromFile("../start_image/tutorial.png");
    start_game.buttontexture.loadFromFile(("../start_image/start_game.png"));
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    tutorial_start.render(NULL);
    SDL_RenderPresent( gRenderer );
    SDL_Event tutorial_start_event;
    while(!quit) {
        while (SDL_PollEvent(&tutorial_start_event) != 0) {
            if (tutorial_start_event.type == SDL_QUIT) quit = true;
            tutorial.handleEvent(&tutorial_start_event);
            start_game.handleEvent(&tutorial_start_event);
            backto_character.handleEvent(&tutorial_start_event);
        }
        if (tutorial_start_event.type == SDL_QUIT) return;
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        tutorial_start.render(NULL);
        bool big_tutorial = 1, big_startgame = 1, big_back = 1;
        if(tutorial.CurrentSprite==BUTTON_SPRITE_MOUSE_OUT) big_tutorial = 0;
        if(start_game.CurrentSprite==BUTTON_SPRITE_MOUSE_OUT) big_startgame = 0;
        if(backto_character.CurrentSprite==BUTTON_SPRITE_MOUSE_OUT) big_back = 0;
        tutorial.rectrender(big_tutorial);
        start_game.circlerender(big_startgame);
        backto_character.rectrender(big_back);
        SDL_RenderPresent(gRenderer);
        if(start_game.CurrentSprite==BUTTON_SPRITE_MOUSE_UP) {
            if(Mode==1) cout << endl << "Final mode = PVE" << endl;
            else if(Mode==2) cout << endl << "Final mode = PVP" << endl;
            cout << "Final total player = " << Player_number << endl;
            cout << "Character = ";
            for(int i = 0; i<Player_number; i++) cout << character_picture[i] << " ";
            cout << endl << "start game!!!" << endl;
            break;
        }
        if(tutorial.CurrentSprite==BUTTON_SPRITE_MOUSE_UP) {
            Tutorial();
            break;
        }
        if(backto_character.CurrentSprite==BUTTON_SPRITE_MOUSE_UP) {
            Choosecharacter();
            break;
        }
    }
}
void Tutorial(){
    cout << "tutorial" << endl;
    SDL_Rect back_dest = {900, 600, 200, 100};
    Texture tutorial;
    RectButton back(back_dest);
    tutorial.loadFromFile("../start_image/tutorial_background.png");
    back.buttontexture.loadFromFile("../start_image/back.png");
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    tutorial.render(NULL);
    SDL_RenderPresent( gRenderer );
    SDL_Event tutorial_event;
    while(!quit) {
        while (SDL_PollEvent(&tutorial_event) != 0) {
            if (tutorial_event.type == SDL_QUIT) quit = true;
            back.handleEvent(&tutorial_event);
        }
        if (tutorial_event.type == SDL_QUIT) return;
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        tutorial.render(NULL);
        bool big = 1;
        if(back.CurrentSprite==BUTTON_SPRITE_MOUSE_OUT) big = 0;
        if(back.CurrentSprite==BUTTON_SPRITE_MOUSE_OUT) big = 0;
        back.rectrender(big);
        SDL_RenderPresent(gRenderer);
        if(back.CurrentSprite==BUTTON_SPRITE_MOUSE_UP) {
            Tutorial_start();
            break;
        }
    }
}



