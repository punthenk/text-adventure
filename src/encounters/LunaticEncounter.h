/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include "Encounter.h"
#include "Enemy.h"
#include "Parser.h"

enum class RequiredAction : std::uint8_t {
    Attack,
    Dodge,
    Block,
    Any,
};

struct RoundEvent {
    string telegraph;
    RequiredAction required_action;
    string success_message;
    string failure_message;
    int damage_if_fail;
    int damage_if_success = 0;
};

class LunaticEncounter : public Encounter {
public:
    LunaticEncounter();

    void onStart(Player& player) override;
    bool isActive() const override;
    void runRound(Player& player) override;

private:
    Parser parser;
    Enemy enemy;
    static const std::vector<RoundEvent> round_events;
    int countdown_seconds = 5;
    int player_attack_damage = 10;
    bool matchesRequiredAction(const string& input, RequiredAction required_action) const;
};
