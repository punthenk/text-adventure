/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "Key.h"
#include <iostream>
#include "Player.h"
#include "CommandType.h"

Key::Key() {
    name = ItemType::Key;
    weight = 1;
    description = "A key to open locked doors";
    use_guide = "To use this item type `use key direction` to unlock a locked room in that direction";
    is_one_time_use = true;
}

void Key::use(UseContext ctx) {
    Room* room_to_open = ctx.player->current_room->getExit(ctx.direction);
    if (room_to_open == nullptr) {
        std::cout << "In that direction, no room exits..." << std::endl;
        return;
    }

    room_to_open->unlock();
}
