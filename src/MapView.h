#pragma once

#include <map>
#include <utility>
#include <set>
#include "Canvas.h"
#include "CommandType.h"
#include "Room.h"

struct Bounds {
    int minX, maxX, minY, maxY;
};

class MapView {
public:
    MapView(Room* player_current_room);
    void draw();

private:
    Room* current_room;
    void calculatePositions(Room *room, int x, int y, std::map<Room *, std::pair<int, int>> &positions,
                            std::set<Room*> &visited);
    Bounds calculateBounds(const std::map<Room *, std::pair<int, int> > &positions);
    Canvas buildCanvas(const std::map<Room *, std::pair<int, int> > &positions);
    std::pair<int, int> directionToOffset(Direction dir);
};
