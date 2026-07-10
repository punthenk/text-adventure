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
    const string& getUseGuide() const { return use_guide; };

protected:
    ItemType name;
    string description;
    string use_guide;
    int weight;
};