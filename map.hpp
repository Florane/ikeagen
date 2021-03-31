#pragma once
#include "room.hpp"

//Room fartory
//Returns appropriate room with produceRoom method

class Map
{
public:
    Room* produceRoom(int x, int y);//returns room of a random type
};
