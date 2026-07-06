#include "MapView.h"
#include <set>

MapView::MapView() {

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
    if (visited.find(room) == visited.end()) {
        return;
    }

    visited.insert(room);
    positions[room] = {x, y};

    for (const auto& [dir, neighbor] : room->getExits()) {
        auto [dx, dy] = directionToOffset(dir);
        calculatePositions(neighbor, x + dx, y + dy, positions, visited);
    }
}
