/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

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
    void damage(int amount);
    void heal(int amount);
    bool setItemInInventory(ItemType item_type, Item* item); // Temporary

    bool takeFromChest(ItemType item_type);
    bool dropToChest(ItemType item_type);

    Inventory backpack;
    Room* current_room;

private:
    int backpack_space;
    int health;
};
