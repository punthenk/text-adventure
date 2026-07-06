#pragma once

#include "CommandType.h"
#include <map>
#include <string>

using std::string;

class CommandLibrary {
public:
    CommandLibrary();
    bool isValidCommandWord(string command);
    bool isValidDirection(string command);

    string getCommandsString();

    static string directionToString(Direction direction);

    template<typename EnumType>
    EnumType lookup(const std::map<string, EnumType> &table, const string &word, EnumType fallback) {
        if (word.empty())
            return fallback;

        const auto it = table.find(word);
        if (it != table.end())
            return it->second;
        return EnumType::Unknown;
    }

    std::map<string, CommandType> getValidCommands() const;
    std::map<string, Direction> getValidDirections() const;

private:
    std::map<string, CommandType> valid_commands;
    std::map<string, Direction> valid_directions;
};

