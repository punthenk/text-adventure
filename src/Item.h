/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include <string>
#include "CommandType.h"

class Player;
class Room;

using std::string;

struct UseContext {
    Player* player;
    std::optional<Direction> direction;
};

class Item {
public:
    Item() = default;
    virtual ~Item() = default;
    virtual bool use(UseContext ctx) = 0;

    ItemType getName() const { return name; }
    int getWeight() const { return weight; }
    const string& getDescription() const { return description; }
    const string& getUseGuide() const { return use_guide; }
    bool isOneTimeUse() const { return is_one_time_use; }

protected:
    ItemType name;
    string description;
    string use_guide;
    int weight;
    bool is_one_time_use;
};