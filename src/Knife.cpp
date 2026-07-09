#include "Knife.h"
#include <iostream>
#include "Player.h"
#include "CommandType.h"

Knife::Knife(int weight) : Item(weight) {
    name = ItemType::Knife;
    description = "A knife you can hurt yourself with. So be careful!";
}

void Knife::use(UseContext ctx) {
    ctx.player->damage(20);
    std::cout << "OUCH! You attacked yourself!" << std::endl;
}
