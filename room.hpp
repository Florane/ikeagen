#pragma once
#include "walls.hpp"
#include "sector.hpp"

//Room data storage and generation
//Can give out and store wall, loot and entity positions

class Room
{
protected:
    Walls wallStorage;
    Sector lootStorage;
    Sector backgroundStorage;
    int xPos,yPos;

    virtual Walls generateWalls() = 0;
    virtual Sector generateLoot() = 0;
    virtual Sector generateBackground() = 0;
    virtual void generateEntities() = 0;
public:
    Room();
    Room(int x,int y);
    Walls produceWalls(); // returns wall data
    Sector produceLoot(); // returns loot position data
    //Sector produceEntities(); // returns entity position data
    Sector produceBackground(); // returns bg color data
};
