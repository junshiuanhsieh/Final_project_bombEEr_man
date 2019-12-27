cmake_minimum_required(VERSION 3.10)
project(bombEEr_man)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})
include_directories(${SDL2_MIXER_INCLUDE_DIR})

add_executable(bombEEr_man main.cpp texture.cpp texture.h button.cpp button.h PVE.cpp PVE.h PVP.cpp PVP.h Map.cpp Map.h Player.cpp Player.h Bomb.cpp Bomb.h Item.cpp Item.h)
target_link_libraries(bombEEr_man ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY})