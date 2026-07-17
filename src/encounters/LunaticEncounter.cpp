/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "LunaticEncounter.h"

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
        CombatCommand::Dodge,
        "Pffehhh, that was close. He nearly hit you...",
        "KABLAMMM!! He hits you with full force!",
        20,
    },
    {
        "OH NO! He's about to attack you can't react fast enough! BLOCK HIM!!!",
        CombatCommand::Block,
        "Well done! You blocked him really well!",
        "BAAAMMMMM! He hits you right in the face...",
        15,
        5,
    },
    {
        "He's turning around. QUICK! Attack him!",
        CombatCommand::Attack,
        "YES! You hit him!",
        "Shit, you missed him! He will not be so happy now...",
        10,
    },
    {
        "You do what you think is best",
        std::nullopt,
        "GOOD ONE!",
        "That was probably not the best option...",
        10,
    }
};

void LunaticEncounter::runRound(Player &player) {
    const RoundEvent& event = Random::pick(round_events);

    Console::typeLine(event.telegraph);
    Command command = parser.getCombatCommand(countdown_seconds);
    bool succeeded = true;
    bool any_action = false;

    if (!event.required_command.has_value())
        any_action = true;

    if (!command.hasCombatCommand()) {
        Console::printWarningLine("YOU HAVE TO TYPE SOMETHING!");
        succeeded = false;
    } else if (!command.hasValidCombatCommand()) {
        Console::printWarningLine("THAT IS NOT A VALID COMMAND!");
        succeeded = false;
    } else if (!any_action && command.combat_command != event.required_command.value()) {
        Console::typeDangerLine("NO! THAT Is not the right one...");
        succeeded = false;
    }

    if (!succeeded) {
        Console::typeWarningLine(event.failure_message);
        player.damage(event.damage_if_fail);
        return;
    }

    Console::typeSuccessLine(event.success_message);

    switch (command.combat_command) {
        case CombatCommand::Attack: {
            enemy.damage(player_attack_damage);
            break;
        }
        case CombatCommand::Block: {
            player_attack_damage += 5;
            player.damage(event.damage_if_success);
            break;
        }
        case CombatCommand::Dodge: {
            enemy.increaseAttackDamage(5);
            break;
        }
        default: {
            Console::typeWarningLine("WHAT?");
            break;
        }
    }

    Console::typeWarning("Your health is now: ");
    player.typeHealth();
    Console::typeWarning("The enemy's health is now: ");
    enemy.typeHealth();
}
