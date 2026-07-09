#include "Knife.h"
#include <iostream>

void Knife::use(UseContext ctx) {
    ctx.player.damage(20);
    std::cout << "OUCH! You attacked yourself!" << std::endl;
}
