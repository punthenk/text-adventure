/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "Parser.h"
#include "Command.h"
#include <iostream>
#include <string>
#include <vector>
#include "CommandType.h"
#include "core/Console.h"

using std::string;

Parser::Parser() { }

Command Parser::getCommand() {
    Console::print("> ");

    const string delimiter = " ";

    string input;
    string words;
    std::getline(std::cin, input);

    std::vector<string> command_strings;
    Command command;

    if (input.empty()) {
        return Command({CommandType::Unknown});
    }

    size_t pos = 0;

    while ((pos = input.find(delimiter)) != string::npos) {
        command_strings.push_back(input.substr(0, pos));
        input.erase(0, pos + 1);
    }

    command_strings.push_back(input);

    command.type = command_library.lookup(command_library.getValidCommands(), command_strings[0], CommandType::Unknown);
    switch (command.type) {
        case CommandType::Help: {
            command.item = command_library.lookup(command_library.getValidItems(), command_strings[1], ItemType::NotSet);
        }
        case CommandType::Go: {
            command.direction = command_library.lookup(command_library.getValidDirections(), command_strings[1], Direction::NotSet);
            break;
        }
        case CommandType::Use: {
            command.item = command_library.lookup(command_library.getValidItems(), command_strings[1], ItemType::NotSet);
            command.direction = command_library.lookup(command_library.getValidDirections(), command_strings[2], Direction::NotSet);
        }
        case CommandType::Take: {
            command.item = command_library.lookup(command_library.getValidItems(), command_strings[1], ItemType::NotSet);
        }
        case CommandType::Drop: {
            command.item = command_library.lookup(command_library.getValidItems(), command_strings[1], ItemType::NotSet);
        }
        default:
            break;
    }

    return command;
}

void Parser::printValidCommands() {
    Console::printInfo("You commands are: ");
    Console::printSuccessLine(command_library.getCommandsString());
}
