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
    void damage(int amount);
    void increaseAttackDamage(int amount);
    bool isAlive() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getAttackDamage() const;
    const string& getName() const;
    void typeHealth() const;

private:
    string name;
    int health;
    int max_health;
    int attack_damage;
};
