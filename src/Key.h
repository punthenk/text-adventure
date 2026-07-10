/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include "Item.h"
#include <string>

using std::string;

class Key : public Item {
public:
    Key(int weight);
    void use(UseContext ctx) override;
};