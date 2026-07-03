#include "Game.h"
#include <iostream>
#include "Command.h"
#include "CommandType.h"

Game::Game() { }

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

bool Game::processCommand(Command command) {
    bool wantToQuit = false;

    switch (command.command_word) {
        case CommandType::Help: {
            printHelp();
            break;
        }
        case CommandType::Status: {
            status();
            break;
        }
        case CommandType::Quit: {
            wantToQuit = true;
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