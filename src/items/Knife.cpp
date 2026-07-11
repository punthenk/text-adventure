/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "Knife.h"
#include <iostream>
#include "Player.h"
#include "CommandType.h"

Knife::Knife() {
    name = ItemType::Knife;
    weight = 1;
    description = "A knife you can hurt yourself with. So be careful! BUT if you're smart it can be used in a useful way ;)";
    use_guide = "To use this item, type `use knife`";
    is_one_time_use = false;
}

UseResult Knife::use(UseContext ctx) {
    ctx.player->damage(20);
    std::cout << "OUCH! You attacked yourself!" << std::endl;

    return {
        .success = true,
        .consume = false
    };
}
