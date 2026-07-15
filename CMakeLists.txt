cmake_minimum_required(VERSION 4.1)
project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)
FetchContent_MakeAvailable(json)

add_executable(game
    src/main.cpp
    src/Command.cpp
    src/CommandLibrary.cpp
    src/Parser.cpp
    src/Game.cpp
    src/Player.cpp
    src/Room.cpp
    src/MapView.cpp
    src/Canvas.cpp
    src/TerminalRawMode.cpp
    src/MapGenerator.cpp
    src/Inventory.cpp
    src/items/Knife.cpp
    src/items/Key.cpp
    src/items/HealItems.cpp
    src/core/Console.cpp
    src/SaveGame.cpp
    src/Enemy.cpp
    src/encounters/LunaticEncounter.cpp
)

target_include_directories(game PRIVATE src)
target_link_libraries(game PRIVATE nlohmann_json::nlohmann_json)
