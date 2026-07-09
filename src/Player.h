#pragma once
#include "Inventory.h"
#include "Room.h"

class Player {
public:
    Player();
    int getBackpackSpace();
    int getHealth();
    bool isAlive();
    void setCurrentRoom(Room* room);
    void damage(int damage);
    bool setItemInInventory(ItemType item_type, Item* item); // Temporary
    Room* current_room;
    Inventory backpack;

private:
    int backpack_space;
    int health;
};
