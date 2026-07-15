/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include <string>

using std::string;

class Enemy {

public:
    Enemy(string name, int health, int attack_damage);
    void takeDamage(int amount);
    bool isDead() const;
    int getHealth() const;
    int getAttackDamage() const;
    const string& getName() const;

private:
    string name;
    int health;
    int attack_damage;
};
