#pragma once

#include "CommandType.h"
#include <map>
#include <string>

using std::string;

class CommandLibrary {
public:
    CommandLibrary();
    bool isValidCommandWord(string command);
    CommandType getCommandType(const string& word);

private:
    std::map<string, CommandType> valid_commands;
};
