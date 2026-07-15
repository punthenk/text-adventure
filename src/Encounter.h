/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

class Player;

class Encounter {
public:
    virtual ~Encounter() = default;
    virtual void onStart(Player& player) = 0;
    virtual void isActive() const = 0;
    virtual void runRound(Player& player) = 0;
};
