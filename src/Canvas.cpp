/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "Canvas.h"

Canvas::Canvas(int width, int height, char fill) : width(width), height(height) {
    grid = std::vector<std::vector<char>>(height, std::vector<char>(width, fill));
}

void Canvas::setChar(int x, int y, char c) {
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;
    grid[y][x] = c;
}

string Canvas::render() {
    string result;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            result += grid[y][x];
        }
        result += '\n';
    }
    return result;
}
