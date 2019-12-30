#ifndef BOMBEER_MAN_PVE_H
#define BOMBEER_MAN_PVE_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "button.h"
#include "texture.h"
#include "Map.h"
#include "Player.h"
#include "Bomb.h"
#include "Item.h"
#include "Location.h"

void PVE();
void PVE_Show_data();
void PVE_initialize();
void PVE_map_initialize(int random_num);

#endif