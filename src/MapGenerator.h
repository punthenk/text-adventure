#pragma once

#include <random>
#include <map>
#include "Room.h"

class MapGenerator {
public:
    MapGenerator(unsigned int seed, int grid_width, int grid_height);
    Room* generate();

private:
    std::mt19937 rng;
    int grid_width, grid_height;

    std::map<std::pair<int, int>, Room*> grid;
    int created_rooms = 0;
    int max_amount_of_rooms;

    void carve(int x, int y, Room* current_room);
    Direction opposite(Direction dir);
};