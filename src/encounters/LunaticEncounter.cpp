/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "LunaticEncounter.h"
#include <thread>
#include <chrono>
#include "core/Console.h"
#include "core/Random.h"
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

const std::vector<RoundEvent> LunaticEncounter::round_events = {
    {
        "NO! He is ready to hit you with ALL his FORCE! DODGE!",
        RequiredAction::Dodge,
        "Pffehhh, that was close. He nearly hit you...",
        "KABLAMMM!! He hits you with full force!",
        20,
    },
    {
        "OH NO! He's about to attack you can't react fast enough! BLOCK HIM!!!",
        RequiredAction::Block,
        "Well done! You blocked him really well!",
        "BAAAMMMMM! He hits you right in the face...",
        15,
        5,
    },
    {
        "He's turning around. QUICK! Attack him!",
        RequiredAction::Attack,
        "YES! You hit him!",
        "Shit, you missed him! He will not be so happy now...",
        10,
    },
    {
        "You do what you think is best",
        RequiredAction::Any,
        "GOOD ONE!",
        "That was probably not the best option...",
        10,
    }
};

bool LunaticEncounter::matchesRequiredAction(const string &input, RequiredAction required_action) const {
    switch (required_action) {
        case RequiredAction::Attack: return input == "attack";
        case RequiredAction::Dodge: return input == "dodge";
        case RequiredAction::Block: return input == "block";
        case RequiredAction::Any: return true;
    }
    return false;
}

void LunaticEncounter::runRound(Player &player) {
    const RoundEvent& event = Random::pick(round_events);

    Console::typeLine(event.telegraph);
    auto input = parser.getInputWithTimeout(countdown_seconds);

    string action = (input.has_value() && !input->empty()) ? (*input)[0] : "";
    bool succeeded = matchesRequiredAction(action, event.required_action);

    if (event.required_action == RequiredAction::Attack && succeeded) {
        enemy.takeDamage(player_attack_damage);
    } else if (event.required_action == RequiredAction::Block && succeeded) {
        player_attack_damage += 5;
    } else if (event.required_action == RequiredAction::Any && succeeded) {
        enemy.takeDamage(player_attack_damage);
    }

    if (succeeded) {
        Console::typeSuccessLine(event.success_message);
        if (event.damage_if_success > 0) {
            player.damage(event.damage_if_success);
        }
    } else {
        Console::typeDangerLine(event.failure_message);
        player.damage(event.damage_if_fail);
    }

    Console::typeWarning("Your health is now: ");
    player.typeHealth();
    Console::typeWarning("The enemy's health is now: ");
    enemy.typeHealth();
}
