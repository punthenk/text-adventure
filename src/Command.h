#pragma once

#include <string>
#include <vector>
#include "CommandType.h"

using std::string;

class Command {
public:
    Command(const std::vector<CommandType>& commands);
    CommandType command_word;
    CommandType second_word;
    CommandType third_word;
    bool isUnknown(CommandType command) const;
};
