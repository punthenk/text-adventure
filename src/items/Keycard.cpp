/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "Keycard.h"
#include "CommandType.h"
#include "core/Console.h"

Keycard::Keycard() {
    name = ItemType::Keycard;
    weight = 3;
    description = "Ohh, a keycard. You need keycards to escape this facility. So you better keep some of these!";
    use_guide = "You need to find the room where you can use the keycards.";
    is_one_time_use = false;
}

bool Keycard::use(UseContext ctx) {
    Console::printWarningLine("You cannot use the keycard here");
    return true;
}
