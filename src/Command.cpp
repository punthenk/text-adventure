#include "Command.h"
#include <string>

using std::string;


bool Command::isUnknown(CommandType command) const {
    return command == CommandType::Unknown;
}

bool Command::hasDirection() {
    return direction != Direction::NotSet;
}

bool Command::hasValidDirection() {
    return direction != Direction::Unknown && direction != Direction::NotSet;
}

bool Command::hasItem() {
    return item != ItemType::NotSet;
}

bool Command::hasValidItem() {
    return item != ItemType::Unknown && item != ItemType::Unknown;
}
