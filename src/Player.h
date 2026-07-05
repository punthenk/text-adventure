#pragma once
#include "Room.h"

class Player {
public:
    Player();
    int getBackpackSpace();
    int getHealth();
    bool isAlive();
    Room* currentRoom;

private:
    int backpack_space;
    int health;
};
