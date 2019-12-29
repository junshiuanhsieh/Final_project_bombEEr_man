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
Map** map = NULL;
extern Player* player;

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
    wall = contain_bomb =  contain_box = 0;
    item = NULL;
    bomb = NULL;
}

Map::Map(Location Location_for_init) : map_loc(Location_for_init){
    character_inside = new bool[Player_number];
    for(int i = 0; i<Player_number; i++) character_inside[i] = 0;
    contain_item = 0;
    which_item = -1;
    wall = contain_bomb = contain_box = 0;
    item = NULL;
    bomb = NULL;
}

//這個其實我不太懂，是box跟障礙物被炸到collapse的意思嗎，還是box會顯現出來。
void Map::collapse(){
    if(contain_box == 1 ) contain_box = 0;
    //不知道被炸到之後不用render是不是我要寫
}

bool Map::met_character(int player){
    if(contain_bomb == 1 || contain_box == 1) return 0;
    else return 1;
}

int Map::item_taken(int player){
    contain_item = 0;
    return which_item;
}

