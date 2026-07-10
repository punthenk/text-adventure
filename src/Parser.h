/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include "CommandLibrary.h"
#include "Command.h"

class Parser {

public:
    Parser();
    Command getCommand();
    void printValidCommands();

private:
    CommandLibrary command_library;
};
