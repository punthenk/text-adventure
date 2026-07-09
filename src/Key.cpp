#include "Key.h"
#include <iostream>
#include "Player.h"
#include "CommandType.h"

Key::Key(int weight) : Item(weight) {
    name = ItemType::Key;
    description = "A key to open locked doors";
}

void Key::use(UseContext ctx) {
    Room* room_to_open = ctx.player->current_room->getExit(ctx.direction);
    if (room_to_open == nullptr) {
        std::cout << "In that direction, no room exits..." << std::endl;
    }

    room_to_open->unlock();
}
