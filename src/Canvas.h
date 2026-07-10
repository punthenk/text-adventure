/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com> *
 */

#pragma once

#include <string>
#include <vector>

using std::string;

class Canvas {
public:
    Canvas(int width, int height, char fill = ' ');
    void setChar(int x, int y, char c);
    string render();

private:
    int width, height;
    std::vector<std::vector<char>> grid;
};