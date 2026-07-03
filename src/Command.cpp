#include "Command.h"
#include <string>

using std::string;

Command::Command(const std::vector<CommandType>& commands) {
    command_word = commands[0];
    second_word = commands[1];
    third_word = commands[2];
}

bool Command::isUnknown(CommandType command) const {
    return command == CommandType::Unknown;
}
