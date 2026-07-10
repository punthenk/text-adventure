/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "Player.h"
#include <iostream>
#include "CommandLibrary.h"
#include "core/Console.h"

Player::Player() : backpack(1000) {
    health = 20;
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
    Console::printLine("Your health is now " + std::to_string(health) + "/100");
}

bool Player::setItemInInventory(ItemType item_type, Item* item) {
    return backpack.put(item_type, item);
}

bool Player::takeFromChest(ItemType item_type) {
    Item* item = current_room->chest.get(item_type);
    if (item == nullptr) {
        Console::printLine("The thing you want to pick up does not exist!");
        return false;
    }

    if (backpack.put(item_type, item)) {
        current_room->chest.removeItem(item_type);
        Console::printLine("The " + CommandLibrary::itemToString(item_type) + " is put in your backpack!");
        return true;
    }

    Console::printLine("There went something wrong tyring to put the item in your backpack :(");
    return false;
}

bool Player::dropToChest(ItemType item_type) {
    Item* item = backpack.get(item_type);

    if (current_room->chest.checkIfItemIsAvailable(item_type)) {
        Console::printLine("This item cannot be droped in this room!");
    } else if (item != nullptr) {
        if (current_room->chest.put(item_type, item)) {
            backpack.removeItem(item_type);
            Console::printLine("The " + CommandLibrary::itemToString(item_type) + " is dropped in the room!");
            return true;
        }
    } else {
        Console::printLine(CommandLibrary::itemToString(item_type) + " is not in your backpack!");
    }

    return false;
}
