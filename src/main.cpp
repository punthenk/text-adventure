#include "Command.h"
#include "Parser.h"
#include <iostream>
#include <string>

using std::string;

struct Player {
    int health = 100;
    int backpack_space = 100;
};

int main() {
    Parser parser = *new Parser;
    bool isFinished = false;
    Player* player = new Player;

    while (player->health > 0 && !isFinished) {
        Command command = parser.getCommand();
    }

    return 0;
}
