#ifndef BOMBEER_MAN_ITEM_H
#define BOMBEER_MAN_ITEM_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Location.h"

class Item {
    friend class Player;
    friend class Map;
    friend class Bomb;
    protected:
        int owner, item_num;  //owner由player呼叫  item_num由constructor初始
        Location item_loc;  //由constructor初始
        bool revealed, taken; //revealed由bomb呼叫，taken由player呼叫
    public:
        Item(Location, int num);  //constructor
        void show();  //由bool revealed, taken判斷要不要render
        virtual void used();
        void taken_by_player(int player_num);  //player get_item(Item &item) 時呼叫
};

class item0 : public Item {
public:
    void used();
};
class item1 : public Item {
    public:
        void used();
};
class item2 : public Item {
public:
    void used();
};
class item3 : public Item {
public:
    void used();
};
class item4 : public Item {
public:
    void used();
};
class item5 : public Item {
public:
    void used();
};
class item6 : public Item {
public:
    void used();
};
class item7 : public Item {
public:
    void used();
};
class item8 : public Item {
public:
    void used();
};
class item9 : public Item {
public:
    void used();
};
class item10 : public Item {
public:
    void used();
};
class item11 : public Item {
public:
    void used();
};

#endif