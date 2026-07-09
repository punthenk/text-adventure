#pragma once

#include <string>
#include "CommandType.h"

class Player;
class Room;

using std::string;

struct UseContext {
    Player* player;
    Direction direction = {};
};

class Item {
public:
    Item(int weight) : weight(weight) { }
    virtual ~Item() = default;
    virtual void use(UseContext ctx) = 0;

    ItemType getName() const { return name; };
    int getWeight() const { return weight; };
    const string& getDescription() const { return description; };

protected:
    ItemType name;
    string description;
    int weight;
};