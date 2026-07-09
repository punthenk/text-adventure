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
    void printHelp(Command command);
    void status();
    void look();
    void goRoom(Command command);
    void useItem(Command command);
    void takeItem(Command command);
    void dropItem(Command command);

    void createRooms();
};
