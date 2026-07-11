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

void Console::printWarningLine(const string &text) {
    std::cout << Color::Yellow << text << Color::Reset << '\n';
}

void Console::printDangerLine(const string &text) {
    std::cout << Color::Red << text << Color::Reset << '\n';
}

void Console::printInfo(const string &text) {
    std::cout << Color::Blue << text << Color::Reset;
}

void Console::printInfoLine(const string &text) {
    std::cout << Color::Blue << text << Color::Reset << '\n';
}

void Console::printSuccessLine(const string &text) {
    std::cout << Color::Green << text << Color::Reset << '\n';
}

// FIXME: Type before typing is done makes corrupt input
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
