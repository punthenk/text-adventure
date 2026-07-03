#pragma once

#include "Parser.h"
#include "Command.h"

class Game {
public:
    Game();
    void play();

private:
    Parser parser;
    struct Player {
        int health = 100;
        bool isAlive = true;
        int backpackSpace;
    };
    Player player;

    bool processCommand(Command command);
    void printHelp();
};
