#pragma once

#include "CommandLibrary.h"
#include "Command.h"

class Parser {

public:
    Parser();
    Command getCommand();

private:
    CommandLibrary commandLibrary;
};
