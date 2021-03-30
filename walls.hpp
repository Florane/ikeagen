#pragma once
#include "sector.hpp"

//Walls storage

class Walls : public Sector
{
    enum Sides //Wall sides: from 0(LEFT) to 3(DOWN)
    {
        LEFT,
        UP,
        RIGHT,
        DOWN
    };
    bool getWall(int x, int y, int side /*wall side*/);//get if the wall exists in this side
    void setWall(int x, int y, int side);//places wall in this side
    void unsetWall(int x, int y, int side);//removes wall in this side
    void setWall(int x, int y, int side, bool clear);//combines setWall and unsetWall
public:
    Walls() : Sector() {};//Default initializers
    Walls(int x, int y) : Sector(x,y) {};
    Walls(const char* name) : Sector(name) {};
    Walls(int x, int y,bool filled) : Sector(x,y,filled?15:0) {};//Generates room filled with walls - needed for some maze generators

    //get if wall on this side exists
    bool left(int x, int y);
    bool up(int x, int y);
    bool right(int x, int y);
    bool down(int x, int y);

    //set the wall on this side
    void leftSet(int x, int y, bool clear, bool bothWays);
    void upSet(int x, int y, bool clear, bool bothWays);
    void rightSet(int x, int y, bool clear, bool bothWays);
    void downSet(int x, int y, bool clear, bool bothWays);

    void addSubSector(int x, int y,Sector sector) override;
    void draw(const char* name);
};
