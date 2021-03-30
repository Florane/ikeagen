#include "furnitureRoom.hpp"
#include "defines.hpp"
#include "procedural.hpp"
#include <vector>
#include <unordered_map>
#include <iostream>

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
        ,{Procedural(SEED_EXIT,xPos,yPos+1).proc()%ROOM_SIZE,ROOM_SIZE-1}};

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

    return walls;
}

void FurnitureRoom::generateLoot()
{

}

void FurnitureRoom::pingEntities()
{

}

Walls FurnitureRoom::produceWalls()
{
    return generateWalls();
}
