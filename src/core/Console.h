/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include <string>
#include <vector>

using std::string;

class Console {
public:
    static void print(const string& text);
    static void printLine(const string& text);
    static void flush();
};