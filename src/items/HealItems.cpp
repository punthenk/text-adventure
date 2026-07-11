/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "HealItems.h"
#include <iostream>
#include "Player.h"
#include "CommandType.h"

// Vodka
Vodka::Vodka() {
    name = ItemType::Vodka;
    weight = 5;
    description = "Vodka, hmmmm, delicious. Makes you happy ;) you should try!";
    use_guide = "To drink the vodka, type `use vodka`";
    is_one_time_use = true;
}

UseResult Vodka::use(UseContext ctx) {
    ctx.player->heal(30);
    std::cout << "Yeah, very good stuff..." << std::endl;
    return {.success = true};
}

// Medkit
Medkit::Medkit() {
    name = ItemType::Medkit;
    weight = 7;
    description = "A medkit is used to heal yourself. It heals you 40% health";
    use_guide = "To use the medkit, type `use medkit`";
    is_one_time_use = true;
}

UseResult Medkit::use(UseContext ctx) {
    ctx.player->heal(50);
    std::cout << "Pffeewh, that's better." << std::endl;
    return {.success = true};
}
