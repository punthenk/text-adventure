/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "Inventory.h"
#include "CommandLibrary.h"

Inventory::Inventory(int max_weight) : max_weight(max_weight) {
}

bool Inventory::put(ItemType item_type, Item* item) {
    items[item_type] = item;
    return true;
}

bool Inventory::removeItem(ItemType item_type) {
    for (const auto& item : items) {
        if (item.first == item_type) {
            items.erase(item.first);
            return true;
        }
    }
    return false;;
}


Item* Inventory::get(ItemType item_type) {
    for (const auto& item : items) {
        if (item.first == item_type) {
            return item.second;
        }
    }
    return nullptr;
}

bool Inventory::checkIfItemIsAvailable(ItemType item_type) {
    for (const auto& item : items) {
        if (item.first == item_type) {
            return true;
        }
    }
    return false;
}

string Inventory::listItems() {
    string str;
    bool first = true;
    for (auto item : items) {
        if (!first)
            str += ", ";
        str += CommandLibrary::itemToString(item.first);
        first = false;
    }
    return !str.empty() ? str : "is empty";
}
