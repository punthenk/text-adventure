/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "Inventory.h"
#include "CommandLibrary.h"

Inventory::Inventory(int max_weight) : max_weight(max_weight) {
}

void Inventory::put(ItemType item_type, std::unique_ptr<Item> item) {
    items[item_type].push_back(std::move(item));
}

bool Inventory::remove(ItemType item_type) {
    auto it = items.find(item_type);
    if (it == items.end() || it->second.empty())
        return false;

    it->second.pop_back();

    if (it->second.empty())
        items.erase(it);

    return true;
}


Item* Inventory::get(ItemType item_type) {
    auto it = items.find(item_type);
    if (it == items.end())
        return nullptr;

    return it->second.front().get();
}

std::unique_ptr<Item> Inventory::take(ItemType item_type) {
    auto it = items.find(item_type);
    if (it == items.end() || it->second.empty())
        return nullptr;

    std::unique_ptr<Item> item = std::move(it->second.back());
    it->second.pop_back();

    if (it->second.empty())
        items.erase(it);

    return item;
}

// TODO: Do a .find instead of a foreach loop
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
    for (auto& item : items) {
        if (!first)
            str += ", ";
        str += CommandLibrary::itemToString(item.first);
        if (item.second.size() > 1) {
            str += '(' + std::to_string(item.second.size()) + ')';
        }
        first = false;
    }
    return !str.empty() ? str : "is empty";
}
