/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "Enemy.h"

Enemy::Enemy(string name, int health, int attack_damage) : name(name), health(health), attack_damage(attack_damage) {
    max_health = health;
}

void Enemy::takeDamage(int amount) {
    health -= amount;
}

bool Enemy::isAlive() const {
    return health > 0;
}

int Enemy::getHealth() const {
    return health;
}

int Enemy::getMaxHealth() const {
    return max_health;
}

int Enemy::getAttackDamage() const {
    return attack_damage;
}

const string& Enemy::getName() const {
    return name;
}


