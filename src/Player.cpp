/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "Player.h"
#include <iostream>
#include "CommandLibrary.h"
#include "core/Console.h"

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

void Player::setHealth(int amount) {
    health = amount;
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
    Console::printInfo("Your health is now ");
    Console::printSuccessLine(std::to_string(health) + "/100");
}

void Player::setItemInInventory(ItemType item_type, Item* item) {
    std::unique_ptr<Item> item_unique_ptr(item);
    backpack.put(item_type, std::move(item_unique_ptr));
}

bool Player::takeFromChest(ItemType item_type) {
    Item* item = current_room->chest.get(item_type);
    if (item == nullptr) {
        Console::printWarningLine("The thing you want to pick up does not exist!");
        return false;
    }

    backpack.put(item_type, current_room->chest.take(item_type));
    Console::printSuccessLine("The " + CommandLibrary::itemToString(item_type) + " is put in your backpack!");

    return true;
}

bool Player::dropToChest(ItemType item_type) {
    Item* item = backpack.get(item_type);

    if (item != nullptr) {
        current_room->chest.put(item_type, backpack.take(item_type));
        Console::printSuccessLine("The " + CommandLibrary::itemToString(item_type) + " is dropped in the room!");
        return true;
    } else {
        Console::printWarningLine(CommandLibrary::itemToString(item_type) + " is not in your backpack!");
    }

    return false;
}
