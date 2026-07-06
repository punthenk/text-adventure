#include "MapView.h"
#include <iostream>
#include <set>
#include "Canvas.h"

MapView::MapView(Room* current_room) {
    start_room = current_room;
}

void MapView::draw() {
    std::map<Room*, std::pair<int,int>> positions;
    std::set<Room*> visited;
    calculatePositions(start_room, 0, 0, positions, visited);

    Canvas canvas = buildCanvas(positions);
    std::cout << canvas.render();
}

std::pair<int, int> MapView::directionToOffset(Direction dir) {
    switch (dir) {
        case Direction::North: return {0, -1};
        case Direction::East: return {1, 0};
        case Direction::South: return {0, 1};
        case Direction::West: return {-1, 0};
        default: return {0, 0};
    }
}

void MapView::calculatePositions(Room *room, int x, int y, std::map<Room*, std::pair<int, int>>& positions, std::set<Room*>& visited) {
    if (visited.find(room) != visited.end()) {
        return;
    }

    visited.insert(room);
    positions[room] = {x, y};

    for (const auto& [dir, neighbor] : room->getExits()) {
        auto [dx, dy] = directionToOffset(dir);
        calculatePositions(neighbor, x + dx, y + dy, positions, visited);
    }
}

Bounds MapView::calculateBounds(const std::map<Room *, std::pair<int, int>> &positions) {
    int minX = 0, maxX = 0, minY = 0, maxY = 0;
    bool first = true;

    for (const auto& [room, pos] : positions) {
        auto [x, y] = pos;
        if (first) {
            minX = maxX = x;
            minY = maxY = y;
            first = false;
        } else {
            minX = std::min(minX, x);
            maxX = std::max(maxX, x);
            minY = std::min(minY, y);
            maxY = std::max(maxY, y);
        }
    }

    return {minX, maxX, minY, maxY};
}

Canvas MapView::buildCanvas(const std::map<Room*, std::pair<int,int>>& positions) {
    Bounds bounds = calculateBounds(positions);

    int width  = bounds.maxX - bounds.minX + 1;
    int height = bounds.maxY - bounds.minY + 1;

    Canvas canvas(width, height);

    for (const auto& [room, pos] : positions) {
        auto [gridX, gridY] = pos;
        int canvasX = gridX - bounds.minX;
        int canvasY = gridY - bounds.minY;
        canvas.setChar(canvasX, canvasY, '#');
    }

    return canvas;
}