/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include <string>
#include "CommandType.h"

using std::string;

class Command {
public:
    CommandType type = CommandType::Unknown;
    Direction direction = Direction::NotSet;
    ItemType item = ItemType::NotSet;
    CombatCommand combat_command = CombatCommand::NotSet;
    EndCommand end_command = EndCommand::NotSet;

    bool isUnknown(CommandType command) const;
    bool hasDirection();
    bool hasValidDirection();
    bool hasItem();
    bool hasValidItem();
    bool hasCombatCommand();
    bool hasValidCombatCommand();
};
