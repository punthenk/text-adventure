#include "Room.h"
#include "CommandLibrary.h"
#include "CommandType.h"
#include <iostream>

Room::Room(string desc, bool roomIsLocked) {
    description = desc;
    is_locked = roomIsLocked;
}

bool Room::getIsLocked() {
    return is_locked;
}

string Room::getShortDescription() {
    return description;
}

string Room::getLongDescription() {
    string str = "You are ";
    str += description + ".\n";
    str += getExitString();
    return str;
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
    string str = "Exits: ";
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

void Room::unlock() {
    if (is_locked) {
        is_locked = false;
        std::cout << "The room is unlocked!" << std::endl;
        return;
    }
    std::cout << "This room is already open!" << std::endl;
}
