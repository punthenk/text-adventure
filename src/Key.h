#pragma once

#include "Item.h"
#include <string>;

using std::string;

class Key : public Item {
    Key(int weight, string name, string description) : Item(weight, std::move(name), std::move(description)) { }
    void use(Player& player, Room* room) override;
};