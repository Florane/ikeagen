#pragma once
#include "room.hpp"

//Furniture room data storage
//Gives off default room storage

class FurnitureRoom : public Room
{
    Walls generateWalls() override;
    Sector generateLoot() override;
    Sector generateBackground() override;
    void generateEntities() override;
public:
    FurnitureRoom() : Room() {};
    FurnitureRoom(int x,int y) : Room(x,y) {};
};
