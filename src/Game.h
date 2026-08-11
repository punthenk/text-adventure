/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include "Parser.h"
#include "Command.h"
#include "Player.h"
#include "SaveGame.h"
#include <optional>

class Game {
public:
    Game();
    void play();
    static void stop();
    static bool finished;

private:
    Parser parser;
    Player player;
    std::optional<unsigned int> seed;

    bool processCommand(Command command);
    void printWelcome();
    void printHelp(Command command);
    void status();
    void look();
    void goRoom(Command command);
    void useItem(Command command);
    void takeItem(Command command);
    void dropItem(Command command);
    void saveGame();
    void loadGame(SaveData& save_data);
    void createRooms(std::optional<unsigned int> current_room_id = std::nullopt);
};
