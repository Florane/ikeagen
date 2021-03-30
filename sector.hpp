#pragma once
#include <stdint.h>
#include <vector>

//Map data storage

class Sector
{
    std::vector<std::vector<uint8_t> > data;

public:
    Sector();//Default constructor. Size 1x1 filled with 0
    Sector(int x/*size x*/, int y/*size y*/);//Map filled with 0
    Sector(int x, int y, uint8_t data/*default cell data*/);//Any data map
    Sector(const char* name /*save file name*/);//Deserializer constructor

    void set(int x, int y, uint8_t value);//Set value at coordinate x,y
    void setAll(uint8_t value);//Reset map data with value
    uint8_t get(int x, int y);//Get value at cordinate x,y
    unsigned int sizeX();//Get size by X axis
    unsigned int sizeY();//Get size by Y axis

    /*Adds data of another sector to this sector at x,y coordinates.
    Uses x,y as 0,0 coordinates of subsector*/
    virtual void addSubSector(int x, int y,Sector sector);

    void serialize(const char* name);//serializes data to %name file
    void deserialize(const char* name);//deserializes data from %name file
    void print();//test func - outputs data to stdout
};
