#pragma once
#include "room.hpp"

//Furniture room data storage
//Gives off default room storage

class FurnitureRoom : public Room
{
    Walls generateWalls();
    Sector generateLoot();
    Sector generateBackground();
    void pingEntities();
public:
    FurnitureRoom() : Room() {};
    FurnitureRoom(int x,int y) : Room(x,y) {};
    Walls produceWalls();
    Sector produceLoot(); // returns loot position data
    Sector produceEntities(); // returns entity position data
    Sector produceBackground(); // returns bg color data
};
