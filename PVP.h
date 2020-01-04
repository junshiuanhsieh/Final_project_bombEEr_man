#ifndef BOMBEER_MAN_PVP_H
#define BOMBEER_MAN_PVP_H

#include <iostream>
#include <string>
#include <SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "button.h"
#include "texture.h"
#include "Map.h"
#include "Player.h"
#include "Bomb.h"
#include "Item.h"
#include "Location.h"

void PVP();
void PVP_Show_data();
void PVP_initialize();
void PVP_map_initialize(int random_num);

#endif
