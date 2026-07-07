cmake_minimum_required(VERSION 4.1)
project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
)
