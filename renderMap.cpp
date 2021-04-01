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
            float vertex[4][2] = {{x*CELL_SIZE+0.5,(y+1)*CELL_SIZE-0.5},{x*CELL_SIZE+0.5,y*CELL_SIZE+0.5}
                ,{(x+1)*CELL_SIZE-0.5,y*CELL_SIZE+0.5},{(x+1)*CELL_SIZE-0.5,(y+1)*CELL_SIZE-0.5}};
            float vertexShift[4][2] {{0,-1},{1,0},{0,1},{-1,0}};

            for(int i = 0;i < 4;i++)
            {
                vertecies.push_back(sf::Vertex(sf::Vector2f(vertex[i][0]-vertexShift[i][0],vertex[i][1]-vertexShift[i][1]),color));
                if((walls.get(x,y)>>i)%2)
                    {vertecies.push_back(sf::Vertex(sf::Vector2f(vertex[(i+1)%4][0]+vertexShift[i][0]*2,vertex[(i+1)%4][1]+vertexShift[i][1]*2),color));}
                else
                    {vertecies.push_back(sf::Vertex(sf::Vector2f(vertex[i][0]-vertexShift[i][0],vertex[i][1]-vertexShift[i][1]),color));}
            }
            texture.draw(vertecies.data(),vertecies.size(),sf::Lines);
        }
    }
    texture.display();
    return texture.getTexture();
}

void addTexture(int x, int y,sf::RenderTexture* texture,sf::Texture add)
{
    sf::Sprite sprite;
    sprite.setPosition(x*CELL_SIZE*ROOM_SIZE,y*CELL_SIZE*ROOM_SIZE);
    sprite.setTexture(add);
    texture->draw(sprite);
}

sf::Texture RenderMap::drawTexture(int selectTextures)
{
    sf::RenderTexture texture;
    texture.create(CELL_SIZE*W,CELL_SIZE*H);
    texture.clear(sf::Color::White);
    for(int y = Y/ROOM_SIZE; y<(((Y+H)/ROOM_SIZE)+((Y+H)%ROOM_SIZE?1:0)); y++)
    {
        for(int x = X/ROOM_SIZE; x<(((X+W)/ROOM_SIZE)+((X+W)%ROOM_SIZE?1:0)); x++)
        {
            std::cout << x << " " << y << std::endl;
            Room* room = Map().produceRoom(x,y);
            if(selectTextures>>1%2)
                addTexture(x,y,&texture,drawWalls(room));
            texture.display();
        }
    }
    return texture.getTexture();
}
