#include "MapGenerator.h"
#include <algorithm>
#include <iostream>
#include "MapView.h"

MapGenerator::MapGenerator(unsigned int seed, int grid_width, int grid_height) : rng(seed), grid_width(grid_width), grid_height(grid_height) {
    max_amount_of_rooms = 20;
}

Room* MapGenerator::generate() {
    Room* start = new Room("test", false);
    grid[{0, 0}] = start;

    carve(0, 0, start);

    return start;
}

void MapGenerator::carve(int x, int y, Room* current_room) {
    if (created_rooms >= max_amount_of_rooms)
        return;

    grid[{x, y}] = current_room;

    std::vector<Direction> directions = {
        Direction::North,
        Direction::East,
        Direction::South,
        Direction::West,
    };

    std::shuffle(directions.begin(), directions.end(), rng);
    for (Direction dir : directions) {
        if (created_rooms >= max_amount_of_rooms)
            return;

        auto [dx, dy] = MapView::directionToOffset(dir);
        int nx = x + dx;
        int ny = y + dy;

        if (nx < 0 || nx >= grid_width || ny < 0 || ny >= grid_height) {
            continue;
        }

        if (grid.find({nx, ny}) != grid.end()) {
            continue;
        }

        Room* neighbor_room = new Room("test", false);
        grid[{nx, ny}] = neighbor_room;
        current_room->addExit(dir, neighbor_room);
        neighbor_room->addExit(opposite(dir), current_room);

        created_rooms++;
        carve(nx, ny, neighbor_room);
    }
}

Direction MapGenerator::opposite(Direction dir) {
    switch (dir) {
        case Direction::North: return Direction::South;
        case Direction::East: return Direction::West;
        case Direction::South: return Direction::North;
        case Direction::West: return Direction::East;
        default: return Direction::Unknown;
    }
}
