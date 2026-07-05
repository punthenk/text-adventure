#pragma once
#include <map>
#include <string>

using std::string;

class Room {
public:
    Room(string desc, bool roomIsLocked);
    bool getIsLocked();
    string getShortDescription();
    string getLongDescription();
    void AddExit(string direction, Room neighbor);
    std::optional<Room> getExit(const string &direction);
    string getExitString();

private:
    string description;
    std::map<string, Room> exits;
    bool isLocked = false;
};
