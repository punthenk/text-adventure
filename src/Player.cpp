#include "Player.h"

Player::Player() {
    health = 100;
    backpack_space = 20;
}

int Player::getBackpackSpace() {
    return backpack_space;
}

int Player::getHealth() {
    return health;
}

bool Player::isAlive() {
    return health >= 0;
}
