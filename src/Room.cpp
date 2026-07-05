#include "Room.h"

Room::Room(string desc, bool roomIsLocked) {
    description = desc;
    isLocked = roomIsLocked;
}

bool Room::getIsLocked() {
    return isLocked;
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

void Room::addExit(const string &direction, Room* neighbor) {
    exits[direction] = neighbor;
}

Room* Room::getExit(const string& direction) {
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
        str += key;
        first = false;
    }
    return str;
}
