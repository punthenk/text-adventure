#include "CommandLibrary.h"
#include <sstream>
#include <string>


using std::string;

CommandLibrary::CommandLibrary() {
    // Commands
    valid_commands["help"] = CommandType::Help;
    valid_commands["status"] = CommandType::Status;
    valid_commands["look"] = CommandType::Look;
    valid_commands["go"] = CommandType::Go;
    valid_commands["map"] = CommandType::Map;
    valid_commands["quit"] = CommandType::Quit;
    valid_commands["use"] = CommandType::Use;

    // Directions
    valid_directions["north"] = Direction::North;
    valid_directions["east"] = Direction::East;
    valid_directions["south"] = Direction::South;
    valid_directions["west"] = Direction::West;

    // Items
    valid_items["knife"] = ItemType::Knife;
}

bool CommandLibrary::isValidCommandWord(string command) {
    const auto map_index = valid_commands.find(command);
    if (map_index != valid_commands.end()) {
        return true;
    }
    return false;
}

bool CommandLibrary::isValidDirection(string command) {
    const auto it = valid_directions.find(command);
    if (it != valid_directions.end()) {
        return true;
    }
    return false;
}

string CommandLibrary::getCommandsString() {
    std::ostringstream commands;
    bool first = true;
    for (const auto& [key, value] : valid_commands) {
        if (!first)
            commands << ", ";

        commands << key;
        first = false;
    }
    return commands.str();
}

string CommandLibrary::directionToString(Direction direction) {
    switch (direction) {
        case Direction::North: return "north";
        case Direction::East: return "east";
        case Direction::South: return "south";
        case Direction::West: return "west";
        case Direction::Unknown: return "unknown";
        case Direction::NotSet: return "unknown";
    }
    return "unknown";
}

std::map<string, CommandType> CommandLibrary::getValidCommands() const {
    return valid_commands;
}

std::map<string, Direction> CommandLibrary::getValidDirections() const {
    return valid_directions;
}

std::map<string, ItemType> CommandLibrary::getValidItems() const {
    return valid_items;
}
