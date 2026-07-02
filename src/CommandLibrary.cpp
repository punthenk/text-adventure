#include "CommandLibrary.h"
#include <algorithm>
#include <string>
#include <vector>

using std::string;

CommandLibrary::CommandLibrary() {
    validCommands.push_back("help");
    validCommands.push_back("quit");
}

bool CommandLibrary::isValidCommandWord(string command) {
    return std::binary_search(validCommands.begin(), validCommands.end(), command);
}
