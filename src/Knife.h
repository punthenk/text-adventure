#pragma once

#include "Item.h"
#include <string>

using std::string;

class Knife : public Item {
public:
    Knife(int weight, ItemType name, string description) : Item(weight, name, std::move(description)) { }
    void use(UseContext ctx) override;
};