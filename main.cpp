#pragma GCC diagnostic ignored "-Wnarrowing"
#include <iostream>

#include "renderMap.hpp"

int main()
{
    RenderMap map;
    map.drawTexture(2).copyToImage().saveToFile("img.png");
}
