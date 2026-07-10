/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include <cstdint>

enum class CommandType : std::uint8_t {
    Help,
    Quit,
    Status,
    Look,
    Go,
    Map,
    Use,
    Take,
    Drop,
    Unknown,
};

enum class Direction : std::uint8_t {
    North,
    East,
    South,
    West,
    Unknown,
    NotSet
};

enum class ItemType : std::uint8_t {
    Knife,
    Key,
    Unknown,
    NotSet,
};