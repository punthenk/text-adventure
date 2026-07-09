#include "Inventory.h"

Inventory::Inventory(int max_weight) : max_weight(max_weight) {
}

bool Inventory::getItem(ItemType item_type, Item* item) {
    items[item_type] = item;
    return true;
}

Item* Inventory::removeItem(ItemType item_type) {
    for (const auto& item : items) {
        if (item.first == item_type) {
            items.erase(item.first);
            return item.second;
        }
    }
    return nullptr;
}
