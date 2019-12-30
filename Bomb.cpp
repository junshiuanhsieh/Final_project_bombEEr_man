#include "Bomb.h"
#include "Map.h"
#include "Player.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Renderer* gRenderer;
extern int Player_number, Mode;
extern int* character_picture;
extern const int Total_item;
extern Map** map;
extern Player* player;
extern int bomb_num;

Bomb::Bomb() : clk(clock()){
    bomb_distance = 1;
}
Bomb::Bomb(Location loc, int distance, int player_num) : bomb_loc(loc), bomb_distance(distance), clk(clock()), owner(player_num){}
Bomb::Bomb(const Bomb &copy): clk(copy.clk){
    bomb_loc = copy.bomb_loc;
    bomb_distance = copy.bomb_distance;
    owner = copy.owner;
}
Bomb Bomb::operator=(const Bomb & copy){
    clk = copy.clk;
    bomb_loc = copy.bomb_loc;
    bomb_distance = copy.bomb_distance;
    owner = copy.owner;
}
Location Bomb::bomb_right(){
    Location bombRight;
    if (bomb_loc.x!=15) bombRight.x=bomb_loc.x+bomb_distance;
    bombRight.y=bomb_loc.y;
    return bombRight;
}
Location Bomb::bomb_left(){
    Location bombLeft;
    if (bomb_loc.x!=0) bombLeft.x=bomb_loc.x-bomb_distance;
    bombLeft.y=bomb_loc.y;
    return bombLeft;
}
Location Bomb::bomb_up(){
    Location bombUp;
    if (bomb_loc.x!=0) bombUp.y=bomb_loc.y-bomb_distance;
    bombUp.x=bomb_loc.x;
    return bombUp;
}
Location Bomb::bomb_down(){
    Location bombDown;
    if (bomb_loc.x!=10) bombDown.y=bomb_loc.y+bomb_distance;
    bombDown.x=bomb_loc.x;
    return bombDown;
}
Bomb* Bomb::bomb_explode(int num, Bomb * bomb){
    bomb_num--;
    Bomb* temp_bomb;
    temp_bomb= new Bomb [bomb_num];
    Bomb* temptempbomb;
    temptempbomb = bomb;
    for(int i = 0; i<num; i++) temp_bomb[i] = Bomb(bomb[i]);
    for(int i = num; i<bomb_num; i++) temp_bomb[i] = Bomb(bomb[i+1]);
    bomb = temp_bomb;
    temp_bomb = temptempbomb;
    map[bomb_loc.x][bomb_loc.y].contain_bomb = 0;
    map[bomb_loc.x][bomb_loc.y].bomb = NULL;
    player[owner].bomb_left++;
    delete [] temp_bomb;
    return bomb;
}
void Bomb::changemap(Location bombLoc){
    for ( int k=0 ; k <Player_number ; ++k){
        if (map[map[bombLoc.x][bombLoc.y].character_inside[k]]){
            bool bombRight = false;
            bool bombLeft = false;
            bool bombUp = false;
            bool bombDown = false;
            for ( int i=bombLoc.x+1 ; i< bomb_right().x ; ++i ){
                for ( int j=0 ; j<Player_number ; ++j ){
                    if ( map[i][bomb_right().y].character_inside[j] ) {
                        bombRight=true;
                        map[i][bomb_right().y].collapse();
                        player[j].dead();
                        player[k].score+=10000;
                        break;
                    }
                }
                if ( bombRight ) break;

                if ( map[i][bomb_right().y].contain_item ) {
                    bombRight=true;
                    map[i][bomb_right().y].box->box_destroyed();
                    map[i][bomb_right().y].item->show();
                    SDL_Delay(1000);
                    map[i][bomb_right().y].item->taken=true;
                    player[k].get_item(map[i][bomb_right().y].item);
                }
                if ( bombRight ) break;

                if (map[i][bomb_right().y].contain_emptybox){
                    bombRight=true;
                    map[i][bomb_right().y].box->box_destroyed();
                }
                if ( bombRight ) break;
            }
            for ( int i=bombLoc.x-1 ; i> bomb_left().x ; --i ){
                for ( int j=0 ; j<Player_number ; ++j ){
                    if ( map[i][bomb_left().y].character_inside[j] ) {
                        bombLeft=true;
                        map[i][bomb_left().y].collapse();
                        player[j].dead();
                        player[k].score+=10000;
                        break;
                    }
                }
                if ( bombLeft ) break;

                if ( map[i][bomb_left().y].contain_item ) {
                    bombLeft=true;
                    map[i][bomb_left().y].box->box_destroyed();
                    map[i][bomb_left().y].item->show();
                    SDL_Delay(1000);
                    map[i][bomb_left().y].item->taken=true;
                    player[k].get_item(map[i][bomb_left().y].item);
                }
                if ( bombLeft ) break;

                if (map[i][bomb_left().y].contain_emptybox){
                    bombLeft=true;
                    map[i][bomb_left().y].box->box_destroyed();
                }

                if ( bombLeft ) break;
            }
            for ( int i=bombLoc.y-1 ; i> bomb_up().y ; --i ){
                for ( int j=0 ; j<Player_number ; ++j ){
                    if ( map[bomb_up().x][i].character_inside[j] ) {
                        bombUp=true;
                        map[bomb_up().x][i].collapse();
                        player[j].dead();
                        player[k].score+=10000;
                        break;
                    }
                }
                if ( bombUp ) break;

                if ( map[bomb_up().x][i].contain_item ) {
                    bombUp=true;
                    map[bomb_up().x][i].box->box_destroyed();
                    map[bomb_up().x][i].item->show();
                    SDL_Delay(1000);
                    map[bomb_up().x][i].item->taken=true;
                    player[k].get_item(map[bomb_up().x][i].item);
                }
                if ( bombUp ) break;

                if (map[bomb_up().x][i].contain_emptybox){
                    bombUp=true;
                    map[bomb_up().x][i].box->box_destroyed();
                }

                if ( bombUp ) break;
            }
            for ( int i=bombLoc.y+1 ; i< bomb_down().y ; ++i ){
                for ( int j=0 ; j<Player_number ; ++j ){
                    if ( map[bomb_down().x][i].character_inside[j] ) {
                        bombDown=true;
                        map[bomb_down().x][i].collapse();
                        player[j].dead();
                        player[k].score+=10000;
                        break;
                    }
                }
                if ( bombDown ) break;

                if ( map[bomb_down().x][i].contain_item ) {
                    bombDown=true;
                    map[bomb_down().x][i].box->box_destroyed();
                    map[bomb_down().x][i].item->show();
                    SDL_Delay(1000);
                    map[i][bomb_right().y].item->taken=true;
                    player[k].get_item(map[bomb_down().x][i].item);
                }
                if ( bombDown ) break;

                if (map[bomb_down().x][i].contain_item){
                    bombDown=true;
                    map[bomb_down().x][i].box->box_destroyed();
                }

                if ( bombDown ) break;
            }
        }
    }

}
