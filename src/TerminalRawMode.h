/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include <termios.h>

class TerminalRawMode {
public:
    TerminalRawMode();
    ~TerminalRawMode();

private:
    termios old_settings;
};