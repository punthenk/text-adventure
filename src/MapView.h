#pragma once

#include <map>
#include <utility>
#include "CommandType.h"
#include "Room.h"

class MapView {
public:
    MapView();
    std::pair<int, int> directionToOffset(Direction dir);
    void calculatePositions(Room* room, int x, int y, std::map<Room*, std::pair<int, int>>& positions, std::set<Room*>& visited);

private:
};
