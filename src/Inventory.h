#pragma once

#include <map>
#include <string>
#include "Item.h"
#include "CommandType.h"

using std::string;

class Inventory {
public:
    Inventory(int max_weight);
    bool put(ItemType item_type, Item* item);
    Item* get(ItemType item_type);
    bool removeItem(ItemType item_type);
    bool checkIfItemIsAvailable(ItemType item_type);
    string listItems();

private:
    int max_weight;
    std::map<ItemType, Item*> items;


};
