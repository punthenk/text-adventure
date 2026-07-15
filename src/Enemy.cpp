/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "Enemy.h"

Enemy::Enemy(string name, int health, int attack_damage) : name(name), health(health), attack_damage(attack_damage) { }

void Enemy::takeDamage(int amount) {
    health -= amount;
}

bool Enemy::isDead() const {
    return health <= 0;
}

int Enemy::getHealth() const {
    return health;
}

int Enemy::getAttackDamage() const {
    return attack_damage;
}

const string& Enemy::getName() const {
    return name;
}


