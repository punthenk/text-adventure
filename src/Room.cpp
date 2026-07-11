/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "Room.h"
#include "CommandLibrary.h"
#include "CommandType.h"
#include <iostream>
#include "core/Console.h"

Room::Room(string desc, bool roomIsLocked) {
    description = desc;
    is_locked = roomIsLocked;
}

bool Room::getIsLocked() {
    return is_locked;
}

string Room::getDescription() {
    return description;
}

void Room::addExit(const Direction &direction, Room* neighbor) {
    exits[direction] = neighbor;
}

Room* Room::getExit(const Direction& direction) {
    const auto it = exits.find(direction);
    if (it != exits.end()) {
        return it->second;
    }
    return nullptr;
}

string Room::getExitString() {
    string str = "";
    bool first = true;
    for (const auto& [key, value] : exits) {
        if (!first)
            str += ", ";
        str += CommandLibrary::directionToString(key);
        first = false;
    }
    return str;
}

std::map<Direction, Room *> & Room::getExits() {
    return exits;
}

void Room::markVisited() {
    is_visited = true;
}

bool Room::getIsVisited() const {
    return is_visited;
}

bool Room::unlock() {
    if (is_locked) {
        is_locked = false;
        Console::printSuccessLine("The room is unlocked!");
        return true;
    }
    Console::printWarningLine("This room is already open!");
    return false;
}

bool Room::hasKeyInChest() {
    return chest.checkIfItemIsAvailable(ItemType::Key);
}
