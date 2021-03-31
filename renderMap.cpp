#include "renderMap.hpp"
#include "map.hpp"
#include "sector.hpp"

#include <vector>
#include <iostream>

sf::Texture RenderMap::drawWalls(Room* room)
{
    sf::RenderTexture texture;
    texture.create(CELL_SIZE*ROOM_SIZE,CELL_SIZE*ROOM_SIZE);
    Sector walls = room->produceWalls();

    for(int x = 0;x < ROOM_SIZE;x++)
    {
        for(int y = 0;y < ROOM_SIZE;y++)
        {
            std::vector<sf::Vertex> vertecies;
            sf::Color color = sf::Color(WALL_COLOR);
            int vertex[4][2] = {{x*CELL_SIZE+1,(y+1)*CELL_SIZE-1},{x*CELL_SIZE+1,y*CELL_SIZE}
                ,{(x+1)*CELL_SIZE,y*CELL_SIZE},{(x+1)*CELL_SIZE,(y+1)*CELL_SIZE-1}};

            for(int i = 0;i < 4;i++)
            {
                vertecies.push_back(sf::Vertex(sf::Vector2f(vertex[i][0],vertex[i][1]),color));
                if((walls.get(x,y)>>i)%2)
                    {vertecies.push_back(sf::Vertex(sf::Vector2f(vertex[(i+1)%4][0],vertex[(i+1)%4][1]),color));}
                else
                    {vertecies.push_back(sf::Vertex(sf::Vector2f(vertex[i][0],vertex[i][1]),color));}
            }
            texture.draw(vertecies.data(),vertecies.size(),sf::Lines);
        }
    }
    texture.display();
    return texture.getTexture();
}

sf::Texture RenderMap::drawTexture(int selectTextures)
{
    sf::RenderTexture texture;
    texture.create(CELL_SIZE*W,CELL_SIZE*H);
    texture.clear(sf::Color::White);
    for(int y = Y/ROOM_SIZE; y<((Y+H)/ROOM_SIZE+((Y+H)%ROOM_SIZE)?1:0); y++)
    {
        for(int x = X/ROOM_SIZE; x<((X+W)/ROOM_SIZE+((X+W)%ROOM_SIZE)?1:0); x++)
        {
            sf::Sprite sprite;
            sprite.setPosition(x*CELL_SIZE*ROOM_SIZE,y*CELL_SIZE*ROOM_SIZE);
            Room* room = Map().produceRoom(x,y);
            if(selectTextures>>1%2)
            {
                sf::Texture buffer = drawWalls(room);
                sprite.setTexture(buffer);
                texture.draw(sprite);
            }
            texture.display();
        }
    }
    return texture.getTexture();
}
