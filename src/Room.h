#pragma once
#include <map>
#include <string>
#include "CommandType.h"

using std::string;

class Room {
public:
    Room(string desc, bool roomIsLocked);
    bool getIsLocked();
    string getShortDescription();
    string getLongDescription();
    void addExit(const Direction &direction, Room* neighbor);
    Room* getExit(const Direction &direction);
    string getExitString();
    std::map<Direction, Room*>& getExits();
    void markVisited();
    bool getIsVisited() const;

private:
    string description;
    std::map<Direction, Room*> exits;
    bool is_locked = false;
    bool is_visited = false;
};
