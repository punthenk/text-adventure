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
    Save,
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
    Vodka,
    Medkit,
    Unknown,
    NotSet,
};

enum class CombatCommand : std::int8_t {
    Attack,
    Dodge,
    Block,
    Unknown,
    NotSet,
};