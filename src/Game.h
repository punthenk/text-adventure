#pragma once

#include "Parser.h"
#include "Command.h"
#include "Player.h"

class Game {
public:
    Game();
    void play();

private:
    Parser parser;
    Player player;

    bool processCommand(Command command);
    void printHelp();
    void status();
};
