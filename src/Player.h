#pragma once
#include "Room.h"

class Player {
public:
    Player();
    int getBackpackSpace();
    int getHealth();
    bool isAlive();
    void setCurrentRoom(Room* room);
    void damage(int damage);
    Room* current_room;

private:
    int backpack_space;
    int health;
};
