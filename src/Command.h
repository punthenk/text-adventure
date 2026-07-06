#pragma once

#include <string>
#include <vector>
#include "CommandType.h"

using std::string;

class Command {
public:
    CommandType type = CommandType::Unknown;
    Direction direction = Direction::NotSet;
    bool isUnknown(CommandType command) const;
    bool hasDirection();
    bool hasValidDirection();
};
