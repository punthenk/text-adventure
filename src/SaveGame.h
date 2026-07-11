/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#pragma once

#include <filesystem>
#include "CommandType.h"
#include <nlohmann/json.hpp>


struct SaveData {
    unsigned int seed;
    int health;
    std::vector<ItemType> inventory_items;
};

void to_json(nlohmann::json& j, const SaveData& save);
void from_json(const nlohmann::json& j, SaveData& save);

class SaveGame {
public:
    static std::filesystem::path getSaveDirectory();
    static bool hasSaveFile();

    static void save(const SaveData& data);
    static std::optional<SaveData> load();
};