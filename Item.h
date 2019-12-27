#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
class Item {
    protected:
        int item_num;
        int owner;
        SDL_Point item_loc;
        bool revealed;
    public:
        Item(int item_num);
        void show();
        virtual void used();
        void taken(int player);
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
