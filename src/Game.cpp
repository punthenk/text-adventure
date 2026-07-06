#include "Game.h"
#include <iostream>
#include "Canvas.h"
#include "Command.h"
#include "CommandType.h"

Game::Game() {
    createRooms();
}

void Game::play() {
    bool finished = false;

    while (!finished && player.isAlive()) {
        Command command = parser.getCommand();
        finished = processCommand(command);
    }
    std::cout << "Bye" << std::endl;
}

void Game::printHelp() {
    std::cout << "Here is you help!" << std::endl;
    parser.printValidCommands();
}

void Game::status() {
    std::cout << "Your health is " << player.getHealth() << "/100" << std::endl;
    std::cout << "----------------------" << std::endl;
}

void Game::look() {
    std::cout << player.current_room->getLongDescription() << std::endl;
}

void Game::goRoom(Command command) {
    if (!command.hasDirection()) {
        std::cout << "Go where?" << std::endl;
        return;
    } else if (!command.hasValidDirection()) {
        std::cout << "That is not a valid direction!" << std::endl;
        return;
    }

    Direction dir = command.direction;

    Room* next_room = player.current_room->getExit(dir);
    if (next_room == nullptr) {
        std::cout << "There is not exit found in that direction!" << std::endl;
        return;
    }

    if (!next_room->getIsLocked()) {
        player.current_room = next_room;
        std::cout << player.current_room->getLongDescription() << std::endl;
    } else {
        std::cout << "The room you want to enter is locked" << std::endl;
    }
}

void Game::createRooms() {
    Room* outside = new Room("outside the main entrance of the garage", false);
    Room* hallway = new Room("inside the hallway of the garage", false);
    outside->addExit(Direction::North, hallway);
    hallway->addExit(Direction::South, outside);

    player.current_room = outside;
}

bool Game::processCommand(Command command) {
    bool wantToQuit = false;

    switch (command.type) {
        case CommandType::Help: {
            printHelp();
            break;
        }
        case CommandType::Status: {
            status();
            break;
        }
        case CommandType::Look: {
            look();
            break;
        }
        case CommandType::Quit: {
            wantToQuit = true;
            break;
        }
        case CommandType::Go: {
            goRoom(command);
            break;
        }
        case CommandType::Map: {
            Canvas c(10, 5);
            c.setChar(2, 2, '#');
            c.setChar(5, 1, '#');
            std::cout << c.render();
            break;
        }
        case CommandType::Unknown: {
            std::cout << "I have no clue what you want..." << std::endl;
            break;
        }
        default: {
            std::cout << "I have no clue what you want..." << std::endl;
        }
    }

    return wantToQuit;
}
