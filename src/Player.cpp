/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "Player.h"
#include <iostream>
#include "CommandLibrary.h"

Player::Player() : backpack(1000) {
    health = 100;
    backpack_space = 20;
    current_room = nullptr;
}

int Player::getBackpackSpace() {
    return backpack_space;
}

int Player::getHealth() {
    return health;
}

bool Player::isAlive() {
    return health > 0;
}

void Player::setCurrentRoom(Room *room) {
    current_room = room;
    current_room->markVisited();
}

void Player::damage(int amount) {
    health -= amount;
}

void Player::heal(int amount) {
    health += amount;
    if (health > 100) {
        health = 100;
    }
    std::cout << "Your health is now " << health << "/100" << std::endl;
}

bool Player::setItemInInventory(ItemType item_type, Item* item) {
    return backpack.put(item_type, item);
}

bool Player::takeFromChest(ItemType item_type) {
    Item* item = current_room->chest.get(item_type);
    if (item == nullptr) {
        std::cout << "The thing you want to pick up does not exist!" << std::endl;
        return false;
    }

    if (backpack.put(item_type, item)) {
        current_room->chest.removeItem(item_type);
        std::cout << "The " << CommandLibrary::itemToString(item_type) << " is put in your backpack!" << std::endl;
        return true;
    }

    std::cout << "There went something wrong tyring to put the item in your backpack :(" << std::endl;
    return false;
}

bool Player::dropToChest(ItemType item_type) {
    Item* item = backpack.get(item_type);

    if (current_room->chest.checkIfItemIsAvailable(item_type)) {
        std::cout << "This item cannot be droped in this room!" << std::endl;
    } else if (item != nullptr) {
        if (current_room->chest.put(item_type, item)) {
            backpack.removeItem(item_type);
            std::cout << "The " << CommandLibrary::itemToString(item_type) << " is dropped in the room!" << std::endl;
            return true;
        }
    } else {
        std::cout << CommandLibrary::itemToString(item_type) << " is not in your backpack!" << std::endl;
    }

    return false;
}
