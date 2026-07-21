/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "MapGenerator.h"
#include <algorithm>
#include <random>
#include "items/Key.h"
#include "items/Knife.h"
#include "MapView.h"
#include "encounters/LunaticEncounter.h"
#include "items/HealItems.h"

MapGenerator::MapGenerator(unsigned int seed, int grid_width, int grid_height) : rng(seed), grid_width(grid_width), grid_height(grid_height) {
    max_amount_of_rooms = 30;

    room_descriptions.push_back("You step into a dimly lit concrete chamber.\nThe air is damp, and its very warm. And you're completely alone...");
    room_descriptions.push_back("Rows of abandoned workstations fill the room.\nMost of the monitors are dark, but one still flickers with unreadable text.");
    room_descriptions.push_back("The smell of burnt electronics hangs in the air.\nSparks occasionally jump from a damaged control panel.");
    room_descriptions.push_back("A long corridor stretches into the darkness.\nYour footsteps echo loudly, as if something is listening.");
    room_descriptions.push_back("You enter what appears to be a laboratory.\nBroken glass covers the floor, and overturned equipment lies scattered everywhere.");
}

Room* MapGenerator::generate() {
    Room* start = new Room("in the first test room", false);
    grid[{0, 0}] = start;

    start->chest.put(ItemType::Knife, std::make_unique<Knife>());
    start->chest.put(ItemType::Key, std::make_unique<Key>());
    start->chest.put(ItemType::Vodka, std::make_unique<Vodka>());
    start->chest.put(ItemType::Medkit, std::make_unique<Medkit>());

    generateRooms(0, grid_height - 1, start);

    return start;
}

std::map<int, Room *> MapGenerator::getRooms() const {
    return rooms;
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
            string description;
            if (chance(rng) < 0.8 && room_descriptions.size() > 0) {
                const int random_index = std::uniform_int_distribution<int>(0, room_descriptions.size() - 1)(rng);
                description = room_descriptions[random_index];
                room_descriptions.erase(room_descriptions.begin() + random_index);
            } else {
                description = "";
            }

            Room* neighbor_room = new Room(description, room_is_locked);

            bool this_freely_reachable = parent_freely_reachable && !room_is_locked;
            freely_reachable[neighbor_room] = this_freely_reachable;

            if (chance(rng) < 0.2)
                neighbor_room->encounter = std::make_unique<LunaticEncounter>();

            // Add items
            if (chance(rng) < 0.25) {
                neighbor_room->chest.put(ItemType::Knife, std::make_unique<Knife>());
            }
            if (chance(rng) < 0.12) {
                neighbor_room->chest.put(ItemType::Vodka, std::make_unique<Vodka>());
            }
            if (chance(rng) < 0.06) {
                neighbor_room->chest.put(ItemType::Medkit, std::make_unique<Medkit>());
            }

            if (this_freely_reachable && chance(rng) < 0.5) {
                neighbor_room->chest.put(ItemType::Key, std::make_unique<Key>());
                spare_keys++;
            }

            grid[{nx, ny}] = neighbor_room;
            room->addExit(dir, neighbor_room);
            neighbor_room->addExit(opposite(dir), room);

            active_rooms.push_back(neighbor_room);
            active_positions[neighbor_room] = {nx, ny};
            created_rooms++;
            rooms[neighbor_room->getRoomId()] = neighbor_room;

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
