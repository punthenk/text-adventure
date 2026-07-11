/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "Key.h"
#include "Player.h"
#include "CommandType.h"
#include "core/Console.h"

Key::Key() {
    name = ItemType::Key;
    weight = 1;
    description = "A key to open locked doors";
    use_guide = "To use this item type `use key direction` to unlock a locked room in that direction";
    is_one_time_use = true;
}

bool Key::use(UseContext ctx) {
    if (ctx.direction.has_value()) {
        if (ctx.direction == Direction::NotSet) {
            Console::printWarningLine("Use where?");
            return false;
        } else if (ctx.direction == Direction::Unknown) {
            Console::printWarningLine("That is not a valid direction!");
            return false;
        }
    } else {
        Console::printWarningLine("Which direction?");
        return false;
    }

    Room* room_to_open = ctx.player->current_room->getExit(ctx.direction.value());
    if (room_to_open == nullptr) {
        Console::printWarningLine("In that direction, no room exits...");
        return false;
    }

    if (room_to_open->unlock())
        return true;

    return false;
}
