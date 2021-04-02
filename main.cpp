#pragma GCC diagnostic ignored "-Wnarrowing"
#include <iostream>

#include "renderMap.hpp"
#include "furnitureRoom.hpp"

int main()
{
    RenderMap map;
    map.drawTexture(7).copyToImage().saveToFile("img.png");
}
