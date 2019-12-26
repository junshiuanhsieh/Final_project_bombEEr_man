#include "PVE.h"
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern bool quit;
int* character = NULL;

void PVE(int number){
    //PVEScrolling(number);
    if(quit) return;
    PVEchoosecharacter(number);
    if(quit) return;
    PVE_tutorial_start();
    if(quit) return;

    if(number == 1) PVE1(1);
    else if(number == 2) PVE2(2);
    else if(number == 3) PVE3(3);

}

void PVEchoosecharacter(int number){
    character = new int[number];
    for(int i = 0; i< number; i++) character[i] = -1;
    int TOTAL_CHARACTER_OPTION = 5;
    Texture choosecharacter;
    RectButton characteroption[TOTAL_CHARACTER_OPTION];
    SDL_Rect characteroption_dest[TOTAL_CHARACTER_OPTION], frame[TOTAL_CHARACTER_OPTION];
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
    characteroption[0].buttontexture.loadFromFile("../character_image/character0.png");
    characteroption[1].buttontexture.loadFromFile("../character_image/character1.png");
    characteroption[2].buttontexture.loadFromFile("../character_image/character2.png");
    characteroption[3].buttontexture.loadFromFile("../character_image/character3.png");
    characteroption[4].buttontexture.loadFromFile("../character_image/character4.png");
    choosecharacter.loadFromFile("../PVE_image/choosecharacter_background.png");
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    choosecharacter.render(NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Event chooseevent;
    bool choosen[TOTAL_CHARACTER_OPTION], nextplayer;
    for (int i = 0; i < TOTAL_CHARACTER_OPTION; i++) choosen[i] = 0;

    int start_choose, tempchoose, end_choose;
    for(int i = 0; i < number; i++) {
        nextplayer = 0;
        start_choose = 0;
        end_choose = 4;
        while (choosen[start_choose] == 1) start_choose++;
        while (choosen[end_choose] == 1) end_choose--;
        tempchoose = start_choose;

        while (!quit) {
            while (SDL_PollEvent(&chooseevent) != 0) {
                if (chooseevent.type == SDL_QUIT) {quit = true; return;}
                else if(chooseevent.type == SDL_KEYDOWN) {
                    while(chooseevent.type != SDL_KEYUP) {
                        SDL_PollEvent(&chooseevent);
                        if (chooseevent.type == SDL_QUIT) {quit=true; break;}
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
                        character[i] = tempchoose;
                        choosen[tempchoose] = 1;
                        tempchoose = 0;
                        while (choosen[tempchoose] == 1) tempchoose++;
                        nextplayer = 1;
                    }
                }
            }
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            choosecharacter.render(NULL);
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
            if(character[number-1] == -1) SDL_RenderFillRect(gRenderer, &frame[tempchoose]);
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
        cout << "character[" << i << "] = " << character[i] << endl;
        SDL_Delay(400);
    }
}
void PVE_tutorial_start(){
    SDL_Rect tutorial_dest = {200, 500, 300, 150}, startgame_dest = {700, 400, 300, 300};
    SDL_Point startgame_center = {850, 550};
    Texture tutorial_start;
    RectButton tutorial(tutorial_dest);
    CircleButton start_game(startgame_dest, startgame_center, 150);
    tutorial_start.loadFromFile("../PVE_image/tutorial_start_background.png");
    tutorial.buttontexture.loadFromFile("../PVE_image/tutorial.png");
    start_game.buttontexture.loadFromFile(("../PVE_image/start_game.png"));
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
        }
        if (tutorial_start_event.type == SDL_QUIT) return;
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        tutorial_start.render(NULL);
        bool big_tutorial = 1, big_startgame = 1;
        if(tutorial.CurrentSprite==BUTTON_SPRITE_MOUSE_OUT) big_tutorial = 0;
        if(start_game.CurrentSprite==BUTTON_SPRITE_MOUSE_OUT) big_startgame = 0;
        tutorial.rectrender(big_tutorial);
        start_game.circlerender(big_startgame);
        SDL_RenderPresent(gRenderer);
        if(start_game.CurrentSprite==BUTTON_SPRITE_MOUSE_UP) {
            cout << "start game" << endl;
            break;
        }
        if(tutorial.CurrentSprite==BUTTON_SPRITE_MOUSE_UP) {
            PVE_tutorial();
            break;
        }
    }
}
void PVE_tutorial(){
    cout << "tutorial" << endl;
    SDL_Rect back_dest = {900, 550, 200, 100};
    Texture tutorial;
    RectButton back(back_dest);
    tutorial.loadFromFile("../PVE_image/tutorial_background.png");
    back.buttontexture.loadFromFile("../PVE_image/tutorial_back.png");
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
            PVE_tutorial_start();
            break;
        }
    }
}

void PVE1(int number){
}
void PVE2(int number){
}
void PVE3(int number){
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
