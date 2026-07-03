#include "CommandLibrary.h"
#include <sstream>
#include <string>


using std::string;

CommandLibrary::CommandLibrary() {
    // Main first commands
    valid_commands["help"] = CommandType::Help;
    valid_commands["status"] = CommandType::Status;

    // Quit
    valid_commands["quit"] = CommandType::Quit;
}

bool CommandLibrary::isValidCommandWord(string command) {
    const auto map_index = valid_commands.find(command);
    if (map_index != valid_commands.end()) {
        return true;
    }
    return false;
}

CommandType CommandLibrary::getCommandType(const string& word) {
    const auto map_index = valid_commands.find(word);
    if (map_index != valid_commands.end()) {
        return valid_commands[word];
    }
    return CommandType::Unknown;
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
