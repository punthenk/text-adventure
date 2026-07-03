#pragma once

class Player {
public:
    Player();
    int getBackpackSpace();
    int getHealth();
    bool isAlive();

private:
    int backpack_space;
    int health;
};