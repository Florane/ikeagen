#include "map.hpp"
#include "procedural.hpp"
#include "defines.hpp"

#include "furnitureRoom.hpp"

Room* Map::produceRoom(int x, int y)
{
    int chance = Procedural(SEED_ROOM,x,y).proc()%100;
    if(chance < 100)
        return new FurnitureRoom(x,y);
}
