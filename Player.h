#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Player {
    public:
        Player();
        Player(int num, int form);
        void changescore(int x);
        bool dead();
        void placebomb(int x, int y);
        void move(int dir, int s);
        void get_item(int item);
        void useitem(int item_num);
        bool alive, item[12];
        int score;
        SDL_Point player_loc;
    private:
        int player_num, form;

};



