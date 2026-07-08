#pragma once

#include <string>
#include "Player.h"

using std::string;

class Item {
public:
    Item(int weight, string name, string description) : weight(std::move(weight)), name(std::move(name)), description(description) { }
    virtual ~Item() = default;
    virtual void use(Player& player) = 0;

    const string& getName() const { return name; };
    int getWeight() const { return weight; };
    const string& getDescription() const { return description; };

protected:
    string name;
    string description;
    int weight;
};