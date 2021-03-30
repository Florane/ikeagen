#include "walls.hpp"
#include <fstream>

bool Walls::getWall(int x, int y, int side) {return (get(x,y)>>side)%2;}
void Walls::setWall(int x, int y, int side) {set(x,y,get(x,y)|1<<side);}
void Walls::unsetWall(int x, int y, int side) {set(x,y,get(x,y)^1<<side);}
void Walls::setWall(int x, int y, int side, bool clear)
{
    if(clear){unsetWall(x,y,side);}
    else{setWall(x,y,side);}
}

bool Walls::left(int x, int y) {return getWall(x,y,LEFT);}
bool Walls::up(int x, int y) {return getWall(x,y,UP);}
bool Walls::right(int x, int y) {return getWall(x,y,RIGHT);}
bool Walls::down(int x, int y) {return getWall(x,y,DOWN);}

void Walls::leftSet(int x, int y, bool clear, bool bothWays)
{
    setWall(x,y,LEFT,clear);
    if(bothWays) {setWall(x-1,y,RIGHT,clear);}
}
void Walls::upSet(int x, int y, bool clear, bool bothWays)
{
    setWall(x,y,UP,clear);
    if(bothWays) {setWall(x,y-1,DOWN,clear);}
}
void Walls::rightSet(int x, int y, bool clear, bool bothWays)
{
    setWall(x,y,RIGHT,clear);
    if(bothWays) {setWall(x+1,y,LEFT,clear);}
}
void Walls::downSet(int x, int y, bool clear, bool bothWays)
{
    setWall(x,y,DOWN,clear);
    if(bothWays) {setWall(x,y+1,UP,clear);}
}

void Walls::addSubSector(int x, int y,Sector sector)
{
    for(int xi = 0;xi < sector.sizeX();xi++)
        for(int yi = 0;yi < sector.sizeY();yi++)
            if(x+xi >= 0 && x+xi < sizeX() && y+yi >= 0 && y+yi < sizeY())
                set(x+xi,y+yi,get(x+xi,y+yi) | sector.get(xi,yi));
}

void Walls::draw(const char* name)
{
    std::ofstream file(name);
    for(int y = 0;y < sizeY();y++)
    {
        for(int x = 0;x < sizeX();x++)
        {
            switch (get(x,y))
            {
                case 0:
                    file << "╬";
                    break;
                case 1:
                    file << "╠";
                    break;
                case 2:
                    file << "╦";
                    break;
                case 3:
                    file << "╔";
                    break;
                case 4:
                    file << "╣";
                    break;
                case 5:
                    file << "║";
                    break;
                case 6:
                    file << "╗";
                    break;
                case 7:
                    file << "╥";
                    break;
                case 8:
                    file << "╩";
                    break;
                case 9:
                    file << "╚";
                    break;
                case 10:
                    file << "═";
                    break;
                case 11:
                    file << "╞";
                    break;
                case 12:
                    file << "╝";
                    break;
                case 13:
                    file << "╨";
                    break;
                case 14:
                    file << "╡";
                    break;
                case 15:
                    file << "█";
                    break;
            }
        }
        file << std::endl;
    }
}
