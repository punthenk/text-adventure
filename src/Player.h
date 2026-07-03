#pragma once

class Player {
public:
    Player();
    int getBackpackSpace() const;
    int getHealth() const;
    bool isAlive() const;

private:
    int backpack_space;
    int health;
};