#pragma once
#include <termios.h>

class TerminalRawMode {
public:
    TerminalRawMode();
    ~TerminalRawMode();

private:
    termios old_settings;
};