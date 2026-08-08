/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include "Encounter.h"
#include "Parser.h"

using std::string;

struct PromtEvent {
    string required_command;
    string success_message;
    string failure_message;
};

class EndEncounter : public Encounter {
public:
    EndEncounter();

    void onStart(Player& player) override;
    bool isActive() const override;
    void runRound(Player& player) override;

private:
    Parser parser;
    bool checkIfValidCommand();
    bool is_active = true;

};
