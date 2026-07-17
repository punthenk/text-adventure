/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "Parser.h"
#include "Command.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include "CommandType.h"
#include "TerminalRawMode.h"
#include "core/Console.h"

using std::string;

Parser::Parser() { }

std::vector<string> Parser::splitInput(const string &input) {
    const string delimiter = " ";
    string remaining = input;
    std::vector<string> command_strings;

    if (input.empty()) {
        return command_strings;
    }

    size_t pos = 0;
    while ((pos = remaining.find(delimiter)) != string::npos) {
        command_strings.push_back(remaining.substr(0, pos));
        remaining.erase(0, pos + 1);
    }

    command_strings.push_back(remaining);
    return command_strings;
}

std::vector<string> Parser::getInput() {
    Console::print("> ");

    string input;
    std::getline(std::cin, input);

    return splitInput(input);
}

std::optional<string> Parser::readLineWithTimeout(int seconds) {
    TerminalRawMode raw;

    const int bar_width = 10;
    string buffer;
    auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(seconds);

    auto redraw = [&](int remaining_seconds) {
        int filled = static_cast<int>(std::round(bar_width * (double)remaining_seconds / seconds));
        filled = std::clamp(filled, 0, bar_width);

        std::cout << "\r\033[2K";     // Line 2: to begin, delete line
        std::cout << "\033[1A";       // To line 1
        std::cout << "\r\033[2K";     // Line 1: to begin, delete line

        std::cout << "[" << string(filled, '#') << string(bar_width - filled, '-') << "] " << remaining_seconds << "s";
        std::cout << "\n> " << buffer; // Line 2 again, cursor ends here

        std::cout << std::flush;
    };

    // First time: line 1 and 2 are not drawn yet, so no need for up.
    std::cout << "[" << std::string(bar_width, '#') << "] " << seconds << "s\n> " << std::flush;

    while (true) {
        auto now = std::chrono::steady_clock::now();
        if (now >= deadline) break;

        const auto remaining_ms = std::chrono::duration_cast<std::chrono::milliseconds>(deadline - now).count();
        const int tick_ms = std::min<long>(remaining_ms, 100);

        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        struct timeval tv{tick_ms / 1000, tick_ms % 1000 * 1000};

        int result = select(STDIN_FILENO + 1, &readfds, nullptr, nullptr, &tv);

        if (result > 0 && FD_ISSET(STDIN_FILENO, &readfds)) {
            char c;
            if (read(STDIN_FILENO, &c, 1) <= 0) continue;

            if (c == '\r' || c == '\n') {
                std::cout << "\r\n" << std::flush;
                return buffer;
            } else if (c == 127 || c == 8) {
                if (!buffer.empty()) buffer.pop_back();
            } else if (c == 3) {
                // Ctrl+C
                std::cout << "\r\n" << std::flush;
                return std::nullopt;
            } else if (std::isprint(static_cast<unsigned char>(c))) {
                buffer.push_back(c);
            }
        }

        const int seconds_left = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(deadline - now).count() / 1000);
        redraw(seconds_left);
    }

    // Delete at timeout
    std::cout << "\r\033[2K\033[1A\r\033[2K" << std::flush;
    return std::nullopt;
}

std::optional<std::vector<string> > Parser::getInputWithTimeout(int seconds) {
    auto line = readLineWithTimeout(seconds);
    if (!line.has_value())
        return std::nullopt;

    return splitInput(*line);
}

Command Parser::getCommand() {
    Command command;
    std::vector<string> command_strings = getInput();

    if (command_strings.empty())
        return Command({CommandType::Unknown});

    command.type = command_library.lookup(command_library.getValidCommands(), command_strings[0], CommandType::Unknown);
    if (command.type == CommandType::Unknown)
        command.direction = command_library.lookup(command_library.getValidDirections(), command_strings[0], Direction::Unknown);

    if (command.hasValidDirection())
        return command;

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

Command Parser::getCombatCommand(int seconds) {
    Command command;
    std::optional<std::vector<string>> command_strings = getInputWithTimeout(seconds);

    if (!command_strings.has_value()) {
        command.combat_command = CombatCommand::NotSet;
        return command;
    }

    command.combat_command = command_library.lookup(command_library.getValidCombatCommands(), (*command_strings)[0], CombatCommand::Unknown);
    return command;
}


void Parser::printValidCommands() {
    Console::printInfo("You commands are: ");
    Console::printSuccessLine(command_library.getCommandsString());
}
