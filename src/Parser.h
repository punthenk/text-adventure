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
    std::vector<string> getInput();
    std::optional<std::vector<string>> getInputWithTimeout(int seconds);
    Command getCommand();
    Command getCombatCommand(int seconds);
    void printValidCommands();

private:
    std::vector<string> splitInput(const string& input);
    std::optional<string> readLineWithTimeout(int seconds);
    CommandLibrary command_library;
};
