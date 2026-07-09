#pragma once

#include <string>
#include "Player.h"

using std::string;

struct UseContext {
    Player& player;
    Room* room = nullptr;
    Direction direction = {};
};

class Item {
public:
    Item(int weight, ItemType name, string description) : weight(std::move(weight)), name(name), description(description) { }
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