/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "MapGenerator.h"
#include <algorithm>
#include <random>
#include "Key.h"
#include "Knife.h"
#include "MapView.h"
#include "HealItems.h"

MapGenerator::MapGenerator(unsigned int seed, int grid_width, int grid_height) : rng(seed), grid_width(grid_width), grid_height(grid_height) {
    max_amount_of_rooms = 10;
}

Room* MapGenerator::generate() {
    Room* start = new Room("test", false);
    grid[{0, 0}] = start;

    Item* knife = new Knife();
    Item* key = new Key();
    Item* vodka = new Vodka();
    Item* medkit = new Medkit();

    start->chest.put(ItemType::Knife, knife);
    start->chest.put(ItemType::Key, key);
    start->chest.put(ItemType::Vodka, vodka);
    start->chest.put(ItemType::Medkit, medkit);

    generateRooms(0, grid_height - 1, start);

    return start;
}

void MapGenerator::generateRooms(int start_x, int start_y, Room* start_room) {
    grid[{start_x, start_y}] = start_room;
    active_rooms.push_back(start_room);
    active_positions[start_room] = {start_x, start_y};
    created_rooms = 1;
    std::unordered_map<Room*, bool> freely_reachable;
    freely_reachable[start_room] = true;

    int spare_keys = 0;

    std::uniform_real_distribution<double> chance(0.0, 1.0);

    while (!active_rooms.empty() && created_rooms < max_amount_of_rooms) {
        // 1. Choose which room we expand on
        int chosen_index;
        if (chance(rng) < 0.5) {
            chosen_index = active_rooms.size() - 1;  // Newest -> make path longer
        } else {
            chosen_index = std::uniform_int_distribution<int>(0, active_rooms.size() - 1)(rng); // Random room to expand
        }
        Room* room = active_rooms[chosen_index];
        auto [x, y] = active_positions[room];

        // 2. Shuffle directions for randomness, and then choose the first valid direction
        std::vector<Direction> directions = {
            Direction::North,
            Direction::East,
            Direction::South,
            Direction::West,
        };
        std::shuffle(directions.begin(), directions.end(), rng);

        bool found_valid_direction = false;

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

            bool parent_freely_reachable = freely_reachable[room];

            bool room_is_locked = false;
            if (chance(rng) < 0.30 && spare_keys > 0) {
                room_is_locked = true;
                spare_keys--;
            }

            // Found a valid direction, now make a new room
            Room* neighbor_room = new Room("in a test room", room_is_locked);

            bool this_freely_reachable = parent_freely_reachable && !room_is_locked;
            freely_reachable[neighbor_room] = this_freely_reachable;

            // Add items
            if (chance(rng) < 0.25) {
                Item* knife = new Knife();
                neighbor_room->chest.put(ItemType::Knife, knife);
            }
            if (chance(rng) < 0.12) {
                Item* vodka = new Vodka();
                neighbor_room->chest.put(ItemType::Vodka, vodka);
            }
            if (chance(rng) < 0.06) {
                Item* medkit = new Medkit();
                neighbor_room->chest.put(ItemType::Medkit, medkit);
            }

            if (this_freely_reachable && chance(rng) < 0.5) {
                Item* key = new Key();
                neighbor_room->chest.put(ItemType::Key, key);
                spare_keys++;
            }

            grid[{nx, ny}] = neighbor_room;
            room->addExit(dir, neighbor_room);
            neighbor_room->addExit(opposite(dir), room);

            active_rooms.push_back(neighbor_room);
            active_positions[neighbor_room] = {nx, ny};
            created_rooms++;

            found_valid_direction = true;
            break;
        }

        // 3. If this room does not have a valid direction, the delete the room from valid active_rooms
        if (!found_valid_direction) {
            active_rooms.erase(active_rooms.begin() + chosen_index);
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
