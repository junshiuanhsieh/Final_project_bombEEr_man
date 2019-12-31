#include "Map.h"
#include "Player.h"
#include "Bomb.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern bool quit;
extern int Player_number, Mode;
extern int* character_picture;
extern const int Total_item;
extern Player* player;
Map** map = NULL;
Texture bomb_texture, emptybox_texture, item_texture[12], itembox_texture, explode_texture, cross_texture;

//render圖像那些是main去判斷對不對，我應該只要做回傳變數給main，告訴他情況就好?
//map 裡面實際要放甚麼(人，箱子，以及箱子中的禮物就等PVE和PVP去設定);
//在item裡面加了一個default constructor ，不然我不能呼叫
//把item_taken改成回傳 int ，因為player應該會需要我跟他說他拿到幾號道具吧
//也把met_character設定成回傳int，讓玩家知道現在遇到的是甚麼情況
//然後item要設定一個 = 的operator ，不然我不能初始化
//然後如果box沒有要class(現在)，我會有一個contain_box 的 bool，但我覺得還是要有class box，或是他可以是一個item陣列，
//然後目前我把map那格上面有障礙物的情況也先放在contain box 裡面，contain_box跟contain_item不會同時為一

Map::Map(){
    character_inside = new bool[Player_number];
    for(int i = 0; i<Player_number; i++) character_inside[i] = 0;
    contain_item = 0;
    which_item = -1;
    wall = contain_bomb =  contain_emptybox = 0;
    item = NULL;
    bomb = NULL;
    emptybox = NULL;
    explode_blending = 0;
}

Map::Map(Location Location_for_init) : map_loc(Location_for_init){
    character_inside = new bool[Player_number];
    for(int i = 0; i<Player_number; i++) character_inside[i] = 0;
    contain_item = 0;
    which_item = -1;
    wall = contain_bomb = contain_emptybox = 0;
    item = NULL;
    bomb = NULL;
    emptybox = NULL;
    explode_blending = 0;
}

void Map::collapse(){
    if(contain_emptybox == 1) {
        contain_emptybox = 0;
        emptybox->destroyed = 1;
        emptybox = NULL;
    }
    if(contain_item == 1 && item->destroyed == 0){
        item->destroyed = 1;
    }
    //不知道被炸到之後不用render是不是我要寫
}

bool Map::met_character(int player){
    if(contain_bomb == 1 || contain_emptybox == 1 || wall ==1 || (contain_item&&item->destroyed==0)) return 0;
    else return 1;
}

int Map::item_taken(int player){
    contain_item = 0;
    return which_item;
}

void Map::render_map(){
    SDL_Rect map_rect = {20+60*map_loc.x, 75+60*map_loc.y, 60, 60};
    if(contain_emptybox && emptybox!=NULL && emptybox->destroyed==0){
        emptybox_texture.render(&map_rect);
    }
    else if(contain_item && item!=NULL && item->destroyed==0){
        itembox_texture.render(&map_rect);
    }
    else if(contain_bomb){
        SDL_Rect bomb_rect = {30+60*map_loc.x, 75+60*map_loc.y, 50, 50};
        bomb_texture.render(&bomb_rect);
    }
    if(explode_blending != 0){
        explode_texture.setAlpha(explode_blending);
        explode_texture.render(&map_rect);
        explode_blending -= 15;
    }
    //contain_item && item->destroyed == 1
}

