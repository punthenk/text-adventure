/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include "Item.h"
#include <string>

using std::string;

class Vodka : public Item {
public:
    Vodka();
    bool use(UseContext ctx) override;
};

class Medkit : public Item {
public:
    Medkit();
    bool use(UseContext ctx) override;
};