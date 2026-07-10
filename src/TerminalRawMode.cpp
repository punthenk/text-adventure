/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "TerminalRawMode.h"
#include <unistd.h>

TerminalRawMode::TerminalRawMode() {
    tcgetattr(STDIN_FILENO, &old_settings);
    termios raw = old_settings;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

TerminalRawMode::~TerminalRawMode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
}
