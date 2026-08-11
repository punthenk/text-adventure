/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "Inventory.h"
#include "CommandLibrary.h"
#include "items/HealItems.h"
#include "items/Key.h"
#include "items/Knife.h"

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

    return it->second.back().get();
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

void Inventory::add(ItemType item_type) {
    switch (item_type) {
        case ItemType::Knife: put(ItemType::Knife, std::make_unique<Knife>()); return;
        case ItemType::Key: put(ItemType::Key, std::make_unique<Key>()); return;
        case ItemType::Vodka: put(ItemType::Vodka, std::make_unique<Vodka>()); return;
        case ItemType::Medkit: put(ItemType::Medkit, std::make_unique<Medkit>()); return;
        default: return;
    }
}

bool Inventory::checkIfItemIsAvailable(ItemType item_type) {
    auto it = items.find(item_type);
    if (it != items.end())
        return true;

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

std::map<ItemType, int> Inventory::getItemsForSave() const {
    std::map<ItemType, int> items_map;
    for (auto& item : items) {
        items_map[item.first] = item.second.size();
    }
    return items_map;
}

int Inventory::getAmountOfItemType(ItemType item_type) {
    int amount = 0;
    for (auto& item : items) {
        if (item.first == item_type)
            amount += item.second.size();
    }
    return amount;
}
