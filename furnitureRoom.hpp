#pragma once
#include "room.hpp"

//Furniture room data storage
//Gives off default room storage

class FurnitureRoom : public Room
{
    Walls generateWalls() override;
    Sector generateLoot();
    void pingEntities();
public:
    FurnitureRoom() : Room() {};
    FurnitureRoom(int x,int y) : Room(x,y) {};
    Walls produceWalls();
    Sector produceLoot() override; // returns loot position data
    Sector produceEntities(); // returns entity position data
    Sector produceBackground(); // returns bg color data
};
