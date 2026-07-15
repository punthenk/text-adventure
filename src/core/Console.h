/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include <string>
#include <vector>

using std::string;

namespace Color {
    constexpr const char* Reset = "\033[0m";
    constexpr const char* Red = "\033[31m";
    constexpr const char* Green = "\033[32m";
    constexpr const char* Yellow = "\033[33m";
    constexpr const char* Blue = "\033[34m";
}

class Console {
public:
    static void print(const string& text);
    static void printLine(const string& text);
    static void printWarningLine(const string& text);
    static void printDangerLine(const string& text);
    static void printDanger(const string& text);
    static void printInfo(const string& text);
    static void printInfoLine(const string& text);
    static void printSuccessLine(const string &text);

    static void setColor(const char* color);

    static void typeLine(const string& text, int delay_ms = 35);
    static void type(const string& text, int delay_ms = 35);
    static void typeWarningLine(const string& text, int delay_ms = 35);
    static void typeWarning(const string& text, int delay_ms = 35);
    static void typeDangerLine(const string& text, int delay_ms = 35);
    static void typeDanger(const string& text, int delay_ms = 35);
    static void typeInfoLine(const string& text, int delay_ms = 35);
    static void typeInfo(const string& text, int delay_ms = 35);
    static void typeSuccessLine(const string &text, int delay_ms = 35);
    static void typeSuccess(const string &text, int delay_ms = 35);

    static void flush();
};