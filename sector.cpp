#include "sector.hpp"
#include <fstream>
#include <iostream>

Sector::Sector(int x, int y,uint8_t value)
{
    std::vector<uint8_t> a;
    a.resize(y,value);
    data.resize(x,a);
}
Sector::Sector() : Sector(1,1,0) {}
Sector::Sector(int x, int y) : Sector(x,y,0) {}

void Sector::set(int x, int y, uint8_t value) {if(x >= 0 && x < data.size() && y >= 0 && y < data[0].size()) {data[x][y] = value;}}
void Sector::setAll(uint8_t value)
{
    int x = data.size(), y = data[0].size();
    data.clear();
    std::vector<uint8_t> a;
    a.resize(y,value);
    data.resize(x,a);
}

uint8_t Sector::get(int x, int y) {return (x >= 0 && x < data.size() && y >= 0 && y < data[0].size() ? data[x][y] : 255);}
unsigned int Sector::sizeX() {return data.size();}
unsigned int Sector::sizeY() {return data[0].size();}

void Sector::addSubSector(int x, int y,Sector sector)
{
    for(int xi = 0;xi < sector.data.size();xi++)
        for(int yi = 0;yi < sector.data[0].size();yi++)
            if(x+xi >= 0 && x+xi < data.size() && y+yi >= 0 && y+yi < data[0].size())
                data[x+xi][y+yi] = sector.data[xi][yi];
}

void Sector::serialize(const char* name)
{
    std::ofstream file(name, std::ios::binary);

    std::vector<uint8_t>::size_type buffer = data.size();
    file.write((char*)&buffer,sizeof(buffer));
    buffer = data[0].size();
    file.write((char*)&buffer,sizeof(buffer));

    for(int x = 0;x < data.size();x++)
        for(int y = 0;y < data[0].size();y++)
            file.write((char*)&data[x][y],sizeof(data[x][y]));
}

void Sector::deserialize(const char* name)
{
    data.clear();
    std::ifstream file(name, std::ios::binary);

    std::vector<uint8_t>::size_type X,Y;
    file.read((char*)&X,sizeof(X));
    file.read((char*)&Y,sizeof(Y));

    std::vector<uint8_t> a;
    a.resize(Y, 0);
    data.resize(X, a);

    for(int x = 0;x < X;x++)
        for(int y = 0;y < Y;y++)
            file.read((char*)&data[x][y],sizeof(data[x][y]));
}

void Sector::print()
{
    for(int x = 0;x < data.size();x++)
    {
        for(int y = 0;y < data[0].size();y++)
        {
            std::cout << (int)data[x][y] << " ";
        }
        std::cout << std::endl;
    }
}
