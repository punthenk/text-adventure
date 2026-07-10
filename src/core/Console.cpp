/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "core/Console.h"
#include <iostream>
#include <unistd.h>

void Console::print(const string &text) {
    std::cout << text;
}

void Console::printLine(const string &text) {
    std::cout << text << '\n';
}

void Console::typeLine(const string &text, int delay_ms) {
    const int microseconds = 1000;
    std::vector<char> chars(text.begin(), text.end());
    for (const char c : chars) {
        std::cout << c;
        std::cout.flush();
        usleep(delay_ms * microseconds);
    }
    std::cout << '\n';
}

void Console::flush() {
    std::cout.flush();
}
