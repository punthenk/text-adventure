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
    static string itemToString(ItemType item_type);

    template<typename EnumType>
    EnumType lookup(const std::map<string, EnumType> &table, const string &word, EnumType empty_fallback) {
        if (word.empty())
            return empty_fallback;

        const auto it = table.find(word);
        if (it != table.end())
            return it->second;
        return EnumType::Unknown;
    }

    std::map<string, CommandType> getValidCommands() const;
    std::map<string, Direction> getValidDirections() const;
    std::map<string, ItemType> getValidItems();

private:
    std::map<string, CommandType> valid_commands;
    std::map<string, Direction> valid_directions;
    static std::map<string, ItemType> valid_items;
};

