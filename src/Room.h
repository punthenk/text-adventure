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
    void addExit(const string &direction, Room* neighbor);
    Room* getExit(const string &direction);
    string getExitString();

private:
    string description;
    std::map<string, Room*> exits;
    bool isLocked = false;
};
