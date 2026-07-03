#include "CommandLibrary.h"
#include <string>

using std::string;

CommandLibrary::CommandLibrary() {
    // Main first commands
    valid_commands["help"] = CommandType::Help;

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
