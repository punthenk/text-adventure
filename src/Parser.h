/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include "CommandLibrary.h"
#include "Command.h"
#include <optional>

class Parser {

public:
    Parser();
    std::optional<std::vector<string>> getInputWithTimeout(int seconds);
    Command getCommand();
    Command getCombatCommand(int seconds);
    Command getEndCommand();
    void printValidCommands();
    string getEndCommandString();
    string getEndCommandStringWithTimeout(int seconds);

private:
    std::vector<string> getInput();
    std::vector<string> splitInput(const string& input);
    std::optional<string> readLineWithTimeout(int seconds);
    CommandLibrary command_library;
};
