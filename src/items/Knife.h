/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include "Item.h"
#include <string>

using std::string;

class Knife : public Item {
public:
    Knife();
    UseResult use(UseContext ctx) override;
};