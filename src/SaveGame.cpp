/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "SaveGame.h"
#include <string>
#include <iostream>
#include <fstream>

using std::string;

void to_json(nlohmann::json &j, const SaveData &save) {
    j = nlohmann::json{
        {"seed", save.seed},
        {"health", save.health},
        {"current_room_id", save.current_room_id},
        {"inventory_items", save.inventory_items},
    };
}

void from_json(const nlohmann::json &j, SaveData &save) {
    j.at("seed").get_to(save.seed);
    j.at("health").get_to(save.health);
    j.at("current_room_id").get_to(save.current_room_id);
    j.at("inventory_items").get_to(save.inventory_items);
}

std::filesystem::path SaveGame::getSaveDirectory() {
#ifdef __APPLE__
    std::filesystem::path base = std::filesystem::path(std::getenv("HOME")) / "Library/Application Support";
#endif
    std::filesystem::path saveDir = base / "text-adventure";
    std::filesystem::create_directories(saveDir);
    return saveDir;
}

bool SaveGame::hasSaveFile() {
    std::filesystem::path path = getSaveDirectory() / "save.json";
    return std::filesystem::exists(path);
}

bool SaveGame::deleteSaveFile() {
    std::filesystem::path path = getSaveDirectory() / "save.json";
    if (std::filesystem::remove(path)) {
        return true;
    }
    perror("Error while removing save game file");
    return false;
}

void SaveGame::save(const SaveData &data) {
    const string& file_name = "save.json";
    std::filesystem::path path = getSaveDirectory() / file_name;

    std::ofstream file_stream{path};
    if (!file_stream) {
        std::cerr << "Could not open file " << file_name << std::endl;
        return;
    }

    nlohmann::json j = data;
    file_stream << j.dump(4);
}

std::optional<SaveData> SaveGame::load() {
    if (!hasSaveFile())
        return std::nullopt;

    const string& file_name = "save.json";
    std::filesystem::path path = getSaveDirectory() / file_name;

    std::ifstream file_stream{path};
    nlohmann::json j;
    file_stream >> j;

    try {
        return j.get<SaveData>();
    } catch (nlohmann::json::exception) {
        std::cout << "Error retrieving game data\n";
        return std::nullopt;
    }
}

