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
    void put(ItemType item_type, std::unique_ptr<Item> item);
    Item* get(ItemType item_type);
    std::unique_ptr<Item> take(ItemType item_type);
    bool removeItem(ItemType item_type);
    bool checkIfItemIsAvailable(ItemType item_type);
    string listItems();

private:
    int max_weight;
    // TODO: Have two of the same items in the inventory
    // FIXME: Make sure the Item* is deleted from the heap when using a one time item
    std::map<ItemType, std::vector<std::unique_ptr<Item>>> items;


};
