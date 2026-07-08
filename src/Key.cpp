#include "Key.h"
#include <iostream>

void Key::use(Player& player, Room* room) {
    std::cout << "The door is unlocked" << std::end;
    room->unlock();
}
