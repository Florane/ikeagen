#include "room.hpp"
#include "defines.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>

Room::Room() {xPos = 0;yPos = 0;}
Room::Room(int x,int y) : xPos(x), yPos(y) {}

Walls Room::produceWalls() {}
Sector Room::produceLoot() {} // returns loot position data
// Sector Room::produceEntities() {} // returns entity position data
Sector Room::produceBackground() {} // returns bg color data
