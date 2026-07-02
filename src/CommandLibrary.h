#pragma once

#include <vector>
#include <string> 

using std::string;

class CommandLibrary {
public:
    CommandLibrary();
    bool isValidCommandWord(string command);
    string getCommands();

private:
    std::vector<string> validCommands;
};
