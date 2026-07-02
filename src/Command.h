#pragma once

#include <string>

using std::string;

class Command {

public:
    Command(string first);
    string commandWord;
    bool isUnknown();
};
