#pragma once
#include "walls.hpp"
#include "sector.hpp"

//Room data storage
//Can give out and store wall, loot and entity positions

class Room
{
public:
    int xPos,yPos;
    Room();
    Room(int x,int y);
    virtual Walls produceWalls(); // returns wall data
    // virtual Sector produceLoot(); // returns loot position data
    // virtual Sector produceEntities(); // returns entity position data
    // virtual Sector produceBackground(); // returns bg color data
};
