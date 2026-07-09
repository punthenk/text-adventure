#include "Player.h"

Player::Player() : backpack(1000) {
    health = 100;
    backpack_space = 20;
    current_room = nullptr;
}

int Player::getBackpackSpace() {
    return backpack_space;
}

int Player::getHealth() {
    return health;
}

bool Player::isAlive() {
    return health > 0;
}

void Player::setCurrentRoom(Room *room) {
    current_room = room;
    current_room->markVisited();
}

void Player::damage(int damage) {
    health -= damage;
}

bool Player::setItemInInventory(ItemType item_type, Item* item) {
    return backpack.put(item_type, item);
}
