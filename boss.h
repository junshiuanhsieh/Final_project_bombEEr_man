//#ifndef BOMBEER_MAN_PLAYER_H
//#define BOMBEER_MAN_PLAYER_H
//#include <SDL.h>
//#include "SDL_image.h"
//#include "SDL_ttf.h"
//#include "texture.h"
//#include "Item.h"
//#include "Location.h"
//#include "Bomb.h"
//
//enum Direction{ UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };
//
//class Boss {
//    friend int main(int, char*args[]);
//    friend int quit_restart_home();
//    friend void PVE();
//    friend void PVE_initialize();
//    friend void PVE_Show_data();
//public:
//    Boss();
//    Boss(int num);
//    bool dead();                             //call by class Bomb
//    void move(Direction);
//    void determine_loc();                    //use player_point to determine player_loc
//    void finish_moving();
//    void get_item(Item *);
//    void useitem(Item *);                    //use pointer to enable polymorphism
//    Bomb* putbomb(Bomb *);
//    void boss_render();
//    bool alive;
//    Item * item_owned[12];
//    bool item[12];
//    int score, bomb_distance, bomb_available, bomb_left;
//    Location boss_loc;
//private:
//    int boss_num, rank, rate;
//    Texture picture;
//    SDL_Point boss_point;
//};
//
//#endif
//
