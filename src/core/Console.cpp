/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "core/Console.h"
#include <iostream>

void Console::print(const string &text) {
    std::cout << text;
}

void Console::printLine(const string &text) {
    std::cout << text << '\n';
}

void Console::flush() {
    std::cout.flush();
}
