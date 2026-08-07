/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include <map>
#include <string>
#include <vector>
#include "Item.h"
#include "CommandType.h"
#include <memory>

using std::string;

class Inventory {
public:
    Inventory(int max_weight);
    bool put(ItemType item_type, std::unique_ptr<Item> item);
    Item* get(ItemType item_type);
    std::unique_ptr<Item> take(ItemType item_type);
    void add(ItemType item_type);
    bool remove(ItemType item_type);
    bool checkIfItemIsAvailable(ItemType item_type);
    string listItems();
    std::map<ItemType, int> getItemsForSave() const;
    int getTotalWeight();
    int getFreeWeight();
    int getMaxWeight();
    bool checkIfItemFits(int weight);
    int getAmountOfItemType(ItemType item_type);

private:
    // TODO: Implement Inventory weight
    int max_weight;
    std::map<ItemType, std::vector<std::unique_ptr<Item>>> items;


};
