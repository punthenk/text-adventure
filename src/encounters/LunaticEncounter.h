/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include "Encounter.h"
#include "Enemy.h"
#include "Parser.h"

class LunaticEncounter : public Encounter {
public:
    LunaticEncounter();

    void onStart(Player& player) override;
    bool isActive() const override;
    void runRound(Player& player) override;

private:
    Parser parser;
    Enemy enemy;
};
