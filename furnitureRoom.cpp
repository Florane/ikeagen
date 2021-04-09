#include "furnitureRoom.hpp"
#include "defines.hpp"
#include "procedural.hpp"

#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <filesystem>

void addPossible(std::pair<int, int> cell,std::vector<std::pair<int, int>>* stack,std::vector<std::pair<int, int>>* remove,std::unordered_map<int, bool>* wasChosen,std::unordered_map<int, bool>* exists)
{
    int check[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    for(int i = 0;i < 4;i++)
    {
        if(cell.first+check[i][0] >= 0 && cell.first+check[i][0] < ROOM_SIZE && cell.second+check[i][1] >= 0 && cell.second+check[i][1] < ROOM_SIZE)
        {
                if(exists->contains((cell.first+check[i][0])*ROOM_SIZE+(cell.second+check[i][1])) && remove != nullptr)
                    {remove->push_back({cell.first+check[i][0],cell.second+check[i][1]});}
                else if(!(wasChosen->contains((cell.first+check[i][0])*ROOM_SIZE+(cell.second+check[i][1]))))
                {
                    stack->push_back({cell.first+check[i][0],cell.second+check[i][1]});
                    (*wasChosen)[(cell.first+check[i][0])*ROOM_SIZE+(cell.second+check[i][1])] = true;
                }
        }
    }
}

Walls FurnitureRoom::generateWalls()
{
    int exits[4][2] = {{0,Procedural(SEED_EXIT,xPos,yPos).proc()%ROOM_SIZE}
        ,{Procedural(SEED_EXIT+1,xPos,yPos).proc()%ROOM_SIZE,0}
        ,{ROOM_SIZE-1,Procedural(SEED_EXIT,xPos+1,yPos).proc()%ROOM_SIZE}
        ,{Procedural(SEED_EXIT+1,xPos,yPos+1).proc()%ROOM_SIZE,ROOM_SIZE-1}};

    std::vector<std::pair<int, int>> stack;
    std::unordered_map<int, bool> wasChosen;
    std::unordered_map<int, bool> exists;

    Procedural proc(SEED_ROOM,xPos,yPos);
    int i = proc.rand()%4;
    wasChosen[exits[i][0]*ROOM_SIZE+exits[i][1]] = true;
    exists[exits[i][0]*ROOM_SIZE+exits[i][1]] = true;
    addPossible({exits[i][0],exits[i][1]},&stack,nullptr,&wasChosen,&exists);

    Walls walls(ROOM_SIZE,ROOM_SIZE,true);
    while(stack.size() > 0)
    {
        int selected = proc.rand()%stack.size();
        exists[stack[selected].first*ROOM_SIZE+stack[selected].second] = true;
        wasChosen[stack[selected].first*ROOM_SIZE+stack[selected].second] = true;

        std::vector<std::pair<int, int>> remove;
        addPossible(stack[selected],&stack,&remove,&wasChosen,&exists);

        if(remove.size()>0)
        {
            int connected = proc.rand()%remove.size();
            if(remove[connected].first-stack[selected].first == -1)
                {walls.leftSet(stack[selected].first,stack[selected].second,true,true);}
            else if(remove[connected].first-stack[selected].first == 1)
                {walls.rightSet(stack[selected].first,stack[selected].second,true,true);}
            if(remove[connected].second-stack[selected].second == -1)
                {walls.upSet(stack[selected].first,stack[selected].second,true,true);}
            else if(remove[connected].second-stack[selected].second == 1)
                {walls.downSet(stack[selected].first,stack[selected].second,true,true);}
        }
        stack.erase(stack.begin()+selected);
    }

    walls.leftSet(exits[0][0],exits[0][1],true,true);
    walls.upSet(exits[1][0],exits[1][1],true,true);
    walls.rightSet(exits[2][0],exits[2][1],true,true);
    walls.downSet(exits[3][0],exits[3][1],true,true);

    return walls;
}

Sector FurnitureRoom::generateLoot()
{
    Sector loot(ROOM_SIZE,ROOM_SIZE,0);
    Procedural proc(xPos,yPos,SEED_ROOM);
    Walls walls = produceWalls();

    for(int x = 0;x < ROOM_SIZE;x++)
        for(int y = 0;y < ROOM_SIZE;y++)
            if((walls.get(x,y) == 7 || walls.get(x,y) == 11 || walls.get(x,y) == 13 || walls.get(x,y) == 14) && proc.rand()%3 == 0)
                loot.set(x,y,1);

    return loot;
}

void checkPosition(int x, int y, int color, Sector* background,Walls* walls)
{
    int check[4][3] = {{-1,0,11},{0,-1,7},{1,0,14},{0,1,13}};
    bool isCarpet = false;
    for(int i = 0;i < 4;i++)
        if(walls->get(x+check[i][0],y+check[i][1]) == check[i][2])
            isCarpet = true;

    if(isCarpet)
    {
        background->set(x,y,color);
        for(int i = 0;i < 4;i++)
        {
            if(background->get(x+check[i][0],y+check[i][1]) == 0)
            {
                if(walls->get(x+check[i][0],y+check[i][1]) == check[i][2])
                    {background->set(x+check[i][0],y+check[i][1],color);}
                else if((walls->get(x,y)>>i)%2 == 0)
                    {checkPosition(x+check[i][0],y+check[i][1],color,background,walls);}
            }
        }
    }
}

Sector FurnitureRoom::generateBackground()
{
    Sector background(ROOM_SIZE,ROOM_SIZE,0);
    Walls walls = produceWalls();
    Procedural proc(xPos,yPos,SEED_ROOM);

    for(int x = 0;x < ROOM_SIZE;x++)
        for(int y = 0;y < ROOM_SIZE;y++)
        {
            if(background.get(x,y) == 0)
                checkPosition(x,y,proc.rand()%7+1,&background,&walls);
        }
    return background;
}

void FurnitureRoom::generateEntities()
{

}
