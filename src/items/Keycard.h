/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include "Item.h"
#include <string>

using std::string;

class Keycard : public Item {
public:
    Keycard();
    bool use(UseContext ctx) override;
};
