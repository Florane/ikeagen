#include "room.hpp"
#include "defines.hpp"
#include <fstream>
#include <filesystem>

Room::Room() {xPos = 0;yPos = 0;}
Room::Room(int x,int y) : xPos(x), yPos(y) {}

Walls Room::produceWalls()
{
    if(wallStorage.sizeX() != ROOM_SIZE)
    {
        std::string file = "maps/walls/x" + std::to_string(xPos) + "y" + std::to_string(yPos) + ".dat";
        if(std::filesystem::exists(file.c_str()))
            {wallStorage.deserialize(file.c_str());}
        wallStorage = generateWalls();
        wallStorage.serialize(file.c_str());
    }
    return wallStorage;
}

Sector Room::produceLoot()
{
    if(lootStorage.sizeX() != ROOM_SIZE)
    {
        std::string file = "maps/loot/x" + std::to_string(xPos) + "y" + std::to_string(yPos) + ".dat";
        if(std::filesystem::exists(file.c_str()))
            {lootStorage.deserialize(file.c_str());}
        lootStorage = generateLoot();
        lootStorage.serialize(file.c_str());
    }
    return lootStorage;
}

Sector Room::produceBackground()
{
    if(backgroundStorage.sizeX() != ROOM_SIZE)
    {
        std::string file = "maps/background/x" + std::to_string(xPos) + "y" + std::to_string(yPos) + ".dat";
        if(std::filesystem::exists(file.c_str()))
            {backgroundStorage.deserialize(file.c_str());}
        backgroundStorage = generateBackground();
        backgroundStorage.serialize(file.c_str());
    }
    return backgroundStorage;
}
