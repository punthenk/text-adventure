#pragma once
//
// Created by Michiel Nijenhuis on 02/07/2026.
//

enum class CommandType {
    Help,
    Quit,
    Status,
    Look,
    Go,
    Unknown,
};

enum class Direction {
    North,
    East,
    South,
    West,
    Unknown,
    NotSet
};