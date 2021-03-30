#pragma once
#include <SFML/Graphics.hpp>

class RenderMap
{
public:
    enum Textures
    {
        Background = 1,
        Walls = 2,
        Loot = 4,
        Entities = 8
    };
    RenderTexture drawTexture(int selectTextures);//draw a texture of the rooms

    RenderTexture drawVisible(int selectTextures, int* entityIds);//draw everything visible from entities' positions

    RenderTexture drawPath(int selectTextures, int[2] p1, int[2] p2);//draw a path between point 1 and point 2
};
