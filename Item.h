#ifndef BOMBEER_MAN_ITEM_H
#define BOMBEER_MAN_ITEM_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Map.h"


class Item {
    friend class Player;
    protected:
        int owner, item_num;
        Location item_loc;
        bool revealed, taken;
    public:
        Item(Location, int num);
        void show();
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