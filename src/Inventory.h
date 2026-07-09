#pragma once

#include <map>
#include <string>
#include "Item.h"
#include "CommandType.h"

using std::string;

class Inventory {
public:
    Inventory(int max_weight);
    bool getItem(ItemType item_type, Item* item);
    Item* removeItem(ItemType item_type);
    Item* getItem(ItemType item_type);

private:
    int max_weight;
    std::map<ItemType, Item*> items;


};
