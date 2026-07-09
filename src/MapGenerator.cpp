#include "MapGenerator.h"
#include <algorithm>
#include <iostream>
#include <random>

#include "Knife.h"
#include "MapView.h"

MapGenerator::MapGenerator(unsigned int seed, int grid_width, int grid_height) : rng(seed), grid_width(grid_width), grid_height(grid_height) {
    max_amount_of_rooms = 10;
}

Room* MapGenerator::generate() {
    Room* start = new Room("test", false);
    grid[{0, 0}] = start;

    Item* knife = new Knife(1, ItemType::Knife, "A knife");
    start->chest.put(ItemType::Knife, knife);

    generateRooms(0, grid_height - 1, start);

    return start;
}

void MapGenerator::generateRooms(int startX, int startY, Room* startRoom) {
    grid[{startX, startY}] = startRoom;
    active_rooms.push_back(startRoom);
    active_positions[startRoom] = {startX, startY};
    created_rooms = 1;

    std::uniform_real_distribution<double> chance(0.0, 1.0);

    while (!active_rooms.empty() && created_rooms < max_amount_of_rooms) {
        // 1. Choose which room we expand on
        int chosenIndex;
        if (chance(rng) < 0.5) {
            chosenIndex = active_rooms.size() - 1;  // Newest -> make path longer
        } else {
            chosenIndex = std::uniform_int_distribution<int>(0, active_rooms.size() - 1)(rng); // Random room to expand
        }
        Room* room = active_rooms[chosenIndex];
        auto [x, y] = active_positions[room];

        // 2. Shuffle directions for randomness, and then choose the first valid direction
        std::vector<Direction> directions = {
            Direction::North,
            Direction::East,
            Direction::South,
            Direction::West,
        };
        std::shuffle(directions.begin(), directions.end(), rng);

        bool foundValidDirection = false;

        for (Direction dir : directions) {
            auto [dx, dy] = MapView::directionToOffset(dir);
            int nx = x + dx;
            int ny = y + dy;

            if (nx < 0 || nx >= grid_width || ny < 0 || ny >= grid_height) {
                continue;
            }
            if (grid.find({nx, ny}) != grid.end()) {
                continue;
            }

            // Found a valid direction, now make a new room
            Room* neighborRoom = new Room("in a test room", false);

            if (chance(rng) < 0.25) {
                Item* knife = new Knife(1, ItemType::Knife, "knife");
                neighborRoom->chest.put(ItemType::Knife, knife);
            }

            grid[{nx, ny}] = neighborRoom;
            room->addExit(dir, neighborRoom);
            neighborRoom->addExit(opposite(dir), room);

            active_rooms.push_back(neighborRoom);
            active_positions[neighborRoom] = {nx, ny};
            created_rooms++;

            foundValidDirection = true;
            break;
        }

        // 3. If this room does not have a valid direction, the delete the room from valid active_rooms
        if (!foundValidDirection) {
            active_rooms.erase(active_rooms.begin() + chosenIndex);
        }
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
