#pragma once
#include <SFML/Graphics.hpp>
#include "room.hpp"
#include "defines.hpp"

//Room renderer, making images from generated rooms.

class RenderMap
{
    int X,Y,W,H; // X,Y - starting position, W,H - image size in cells
    sf::Texture drawWalls(Room* room);
    sf::Texture drawLoot(Room* room);
    sf::Texture drawBackground(Room* room);
    sf::Texture drawRooms(Room* room);
public:
    RenderMap() : X(0), Y(0), W(ROOM_SIZE), H(ROOM_SIZE) {};
    RenderMap(int x, int y, int w, int h) : X(x), Y(y), W(w), H(h) {};
    enum Textures//Add together to get appropriate code for textures
    {
        Background = 1,
        Walls = 2,
        Loot = 4,
        Entities = 8,
        FurnitureRooms = 16
    };
    sf::Texture drawTexture(int selectTextures);//draw a texture of the rooms
    sf::Texture drawVisible(int selectTextures, int* entityIds);//draw everything visible from entities' positions
    sf::Texture drawPath(int selectTextures, int p1[2], int p2[2]);//draw a path between point 1 and point 2
};
