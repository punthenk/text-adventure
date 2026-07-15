/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "LunaticEncounter.h"
#include <thread>
#include <chrono>
#include "core/Console.h"
#include <vector>
#include "Player.h"

LunaticEncounter::LunaticEncounter() : enemy("Escaped lunatic prisoner", 100, 15) { }

void LunaticEncounter::onStart(Player &player) {
    Console::typeLine("Oh shit, you are locked up with an escaped lunatic prisoner!");
    Console::typeLine("He is trying to kill you! (TIP: `attack`)");
}

bool LunaticEncounter::isActive() const {
    return enemy.isAlive();
}

void LunaticEncounter::runRound(Player &player) {
    std::vector<string> input = parser.getInput();

    if (input[0] == "attack") {
        int damage = 20;
        enemy.takeDamage(damage);
        Console::typeSuccess("YES! You hit him, his health is now: ");
        enemy.printHealth();
    } else {
        Console::typeWarningLine("NO! THAT DOES NOT DO ANYTHING!");
    }

    Console::typeLine("OH NO! He is preparing for a big...") ;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Console::typeDangerLine("BAAAAAMMMM!!!");

    if (enemy.isAlive()) {
        player.damage(enemy.getAttackDamage());
        Console::typeDanger("HE HIT YOU! Your health is now: ");
        player.typeHealth();
    }
}

