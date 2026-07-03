#include "Player.h"

Player::Player() {
    health = 100;
    backpack_space = 20;
}

int Player::getBackpackSpace() const {
    return backpack_space;
}

int Player::getHealth() const {
    return health;
}

bool Player::isAlive() const {
    return health >= 0;
}
