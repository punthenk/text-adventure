#include "Parser.h"
#include "Command.h"
#include <iostream>
#include <string>
#include <vector>
#include "CommandType.h"

using std::string;

Parser::Parser() { }

Command Parser::getCommand() {
    std::cout << "> "; 

    const string delimiter = " ";

    string input;
    string words;
    std::getline(std::cin, input);

    std::vector<string> command_strings;
    std::vector<CommandType> commands;

    if (input.empty()) {
        return Command({CommandType::Unknown});
    }

    size_t pos = 0;

    while ((pos = input.find(delimiter)) != string::npos) {
        command_strings.push_back(input.substr(0, pos));
        input.erase(0, pos + 1);
    }

    command_strings.push_back(input);

    for (const string& word : command_strings) {
        commands.push_back(commandLibrary.getCommandType(word));
    }

    return Command(commands);
}
