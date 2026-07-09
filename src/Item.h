#pragma once

#include <string>
#include "CommandType.h"

class Player;
class Room;

using std::string;

struct UseContext {
    Player& player;
    Room* room = nullptr;
    Direction direction = {};
};

class Item {
public:
    Item(int weight, ItemType name, string description) : weight(weight), name(name), description(std::move(description)) { }
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