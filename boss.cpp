//#include "boss.h"
//#include "Player.h"
//#include "Bomb.h"
//#include "Map.h"
//
//extern const int SCREEN_WIDTH;
//extern const int SCREEN_HEIGHT;
//extern SDL_Renderer* gRenderer;
//extern int* character_picture;
//extern const int Total_item ;
//extern Map** map;
//extern int bomb_num;
//extern int player_number;
//extern Bomb * bomb;
//
//Boss::Boss(){
//    alive = true;
//    for(int i = 0; i<Total_item; i++) {
//        item[i] = 0;
//        item_owned[i] = NULL;
//    }
//    score = 0;
//    rank = 1;
//    bomb_distance = 2;
//    bomb_available = 3;
//    bomb_left = 3;
//    rate = 8;
//}
//Boss::Boss(int num) : boss_num(num){
//    alive = true;
//    for(int i = 0; i<Total_item; i++) {
//        item[i] = 0;
//        item_owned[i] = NULL;
//    }
//    score = 0;
//    rank = 1;
//    bomb_distance = 2;
//    bomb_available = 3;
//    bomb_left = 3;
//    rate = 8;
//}
//
//
//bool Boss::dead(){
//    alive = false;
//    for(int i = 0; i<Total_item; i++) item_owned[i] = 0;
//    //rank = count_rank;
//}
//void Boss::move(Direction dir){
//    if(this->item[5] == 1){
//        if(dir == UP) dir =DOWN;
//        else if(dir == DOWN) dir =UP;
//        else if(dir == LEFT) dir =RIGHT;
//        else dir = LEFT;
//    }
//    if(dir == UP) {
//        if(boss_point.y >= 105+rate) {
//            if(map[boss_loc.x][boss_loc.y].contain_item ==1 ){
//                get_item(map[boss_loc.x][boss_loc.y].item);
//                map[boss_loc.x][boss_loc.y].item_taken(this->boss_num);
//            }
//
//            bool change_loc = 0, soon_change_loc = 0;
//            if((boss_point.y-rate-75) / 60 != boss_loc.y && boss_loc.y>0) change_loc = 1;
//            if((boss_point.y-30-75) / 60 != boss_loc.y && boss_loc.y>0) soon_change_loc = 1;
//            if(change_loc){
//                if(map[boss_loc.x][boss_loc.y-1].met_character(boss_num)){
//                    boss_point.y -= rate;
//                    map[boss_loc.x][boss_loc.y-1].character_inside[boss_num] = 1;
//                    map[boss_loc.x][boss_loc.y].character_inside[boss_num] = 0;
//                    boss_loc.y--;
//                }
//            }
//            else if(soon_change_loc){
//                if(map[boss_loc.x][boss_loc.y-1].met_character(boss_num)){
//                    boss_point.y -= rate;
//                }
//            }
//            else boss_point.y -= rate;
//        }
//    }
//    else if(dir == DOWN){
//        if(boss_point.y <= 705-rate) {
//            if(map[boss_loc.x][boss_loc.y].contain_item ==1 ){
//                get_item(map[boss_loc.x][boss_loc.y].item);
//                map[boss_loc.x][boss_loc.y].item_taken(this->boss_num);
//            }
//
//            bool change_loc = 0, soon_change_loc = 0;
//            if((boss_point.y+rate-75) / 60 != boss_loc.y && boss_loc.y<11) change_loc = 1;
//            if((boss_point.y+30-75) / 60 != boss_loc.y && boss_loc.y<11) soon_change_loc = 1;
//            if(change_loc){
//                if(map[boss_loc.x][boss_loc.y+1].met_character(boss_num)){
//                    boss_point.y += rate;
//                    map[boss_loc.x][boss_loc.y+1].character_inside[boss_num] = 1;
//                    map[boss_loc.x][boss_loc.y].character_inside[boss_num] = 0;
//                    boss_loc.y++;
//                }
//            }
//            else if(soon_change_loc){
//                if(map[boss_loc.x][boss_loc.y+1].met_character(boss_num)){
//                    boss_point.y += rate;
//                }
//            }
//            else boss_point.y += rate;
//        }
//    }
//    else if(dir == LEFT){
//        if(boss_point.x >= 50+rate) {
//
//            if(map[boss_loc.x][boss_loc.y].contain_item ==1 ){
//                get_item(map[boss_loc.x][boss_loc.y].item);
//                map[boss_loc.x][boss_loc.y].item_taken(this->boss_num);
//            }
//            bool change_loc = 0, soon_change_loc = 0;
//            if((boss_point.x-rate-20) / 60 != boss_loc.x && boss_loc.x>0) change_loc = 1;
//            if((boss_point.x-30-20) / 60 != boss_loc.x && boss_loc.x>0) soon_change_loc = 1;
//            if(change_loc){
//                if(map[boss_loc.x-1][boss_loc.y].met_character(boss_num)){
//                    boss_point.x -= rate;
//                    map[boss_loc.x-1][boss_loc.y].character_inside[boss_num] = 1;
//                    map[boss_loc.x][boss_loc.y].character_inside[boss_num] = 0;
//                    boss_loc.x--;
//                }
//            }
//            else if(soon_change_loc){
//                if(map[boss_loc.x-1][boss_loc.y].met_character(boss_num)){
//                    boss_point.x -= rate;
//                }
//            }
//            else boss_point.x -= rate;
//        }
//    }
//    else if(dir == RIGHT){
//        if(boss_point.x <= 950-rate) {
//
//            if(map[boss_loc.x][boss_loc.y].contain_item ==1 ){
//                get_item(map[boss_loc.x][boss_loc.y].item);
//                map[boss_loc.x][boss_loc.y].item_taken(this->boss_num);
//            }
//            bool change_loc = 0, soon_change_loc = 0;
//            if((boss_point.x+rate-20) / 60 != boss_loc.x && boss_loc.x<16) change_loc = 1;
//            if((boss_point.x+30-20) / 60 != boss_loc.x && boss_loc.x<16) soon_change_loc = 1;
//            if(change_loc){
//                if(map[boss_loc.x+1][boss_loc.y].met_character(boss_num)){
//                    boss_point.x += rate;
//                    map[boss_loc.x+1][boss_loc.y].character_inside[boss_num] = 1;
//                    map[boss_loc.x][boss_loc.y].character_inside[boss_num] = 0;
//                    boss_loc.x++;
//                }
//            }
//            else if(soon_change_loc){
//                if(map[boss_loc.x+1][boss_loc.y].met_character(boss_num)){
//                    boss_point.x += rate;
//                }
//            }
//            else boss_point.x += rate;
//        }
//    }
//    determine_loc();
//
//
//
//}
//void Boss::determine_loc(){
//    boss_loc.x = (boss_point.x-20) / 60;
//    boss_loc.y = (boss_point.y-75) / 60;
//}
//
//void Boss::finish_moving(){
//    boss_point.x = 50 + boss_loc.x*60;
//    boss_point.y = 105 + boss_loc.y*60;
//}
//
//Bomb* Boss::putbomb(Bomb * bomb){
//    bomb_num++;
//    Bomb* temp_bomb;
//    temp_bomb= new Bomb [bomb_num];
//    Bomb* temptempbomb;
//    temptempbomb = bomb;
//    for(int i = 0; i<bomb_num-1; i++) temp_bomb[i] = bomb[i];
//    Bomb newbomb(boss_loc,bomb_distance, boss_num, bomb_num-1);
//    temp_bomb[bomb_num-1] = newbomb;
//    bomb = temp_bomb;
//    map[boss_loc.x][boss_loc.y].bomb = &bomb[bomb_num-1];
//    temp_bomb = temptempbomb;
//    map[boss_loc.x][boss_loc.y].contain_bomb = 1;
//    map[boss_loc.x][boss_loc.y].bomb = & bomb[bomb_num-1];
//    delete [] temp_bomb;
//    return bomb;
//}
//
////這裡要大改 裡面東西是錯的 20190103
//void Boss::get_item(Item * item_get){
//    item[item_get->item_num] = 1 ;
//
//    if(item_get->item_num == 0) {
//        this->bomb_available++;
//        this->bomb_left++;
//    }
//        //增加一格爆炸範圍
//    else if(item_get->item_num == 1){
//        this->bomb_distance ++;
//    }
//        //爆炸威力加到最大
//    else if(item_get->item_num == 2){
//        this->bomb_distance = 9;
//    }
//        //走路速度變快
//    else if(item_get->item_num == 3){
//        this->rate += 3;
//    }
//        //走路速度變慢
//    else if(item_get->item_num == 4){
//        this->rate -= 3;
//    }
//        //逆向寫在move裡面
//    else if(item_get->item_num == 5){
//
//    }
//        //盾牌直接寫在bomb裡面
//    else if(item_get->item_num == 11){
//
//    }
//
//    //item_get->taken_by_bo(boss_num);
//
//
//}
//void Boss::useitem(Item * item){
//    item_owned[item->item_num]--;
//    item->used();
//}
