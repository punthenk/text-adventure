#include "Game.h"
#include <iostream>
#include "Canvas.h"
#include "Command.h"
#include "CommandType.h"
#include "Knife.h"
#include "MapGenerator.h"
#include "MapView.h"

Game::Game() {
    createRooms();

    // Item* knife = new Knife(1, ItemType::Knife, "A knife");
    // player.setItemInInventory(ItemType::Knife, knife);
}

void Game::play() {
    bool finished = false;

    while (!finished && player.isAlive()) {
        Command command = parser.getCommand();
        finished = processCommand(command);
    }
    std::cout << "Bye" << std::endl;
}

void Game::printHelp(Command command) {
    if (!command.hasItem()) {
        std::cout << "Here is you help!" << std::endl;
        std::cout << "(TIP: You can do `help item` to get more info about that item!)" << std::endl;
        parser.printValidCommands();
        return;
    } else if (!command.hasValidItem()) {
        std::cout << "We don't support help for that item" << std::endl;
        return;
    }

    std::cout << "ITEM HELP" << std::endl;
    std::cout << "------------------------" << std::endl;

    Item* item = player.backpack.get(command.item);
    if (item != nullptr) {
        std::cout << "Name: " << CommandLibrary::itemToString(item->getName()) << std::endl;
        std::cout << "Description: " << item->getDescription() << std::endl;
        std::cout << "Guide: " << item->getUseGuide() << std::endl;
        std::cout << "Weight: " << item->getWeight() << " kg" << std::endl;
    } else {
        std::cout << "You need to have that item in your backpack to ask help" << std::endl;
    }
}

void Game::status() {
    std::cout << "Your health is " << player.getHealth() << "/100" << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout << "Your inventory: " << player.backpack.listItems() << std::endl;
}

void Game::look() {
    std::cout << player.current_room->getLongDescription() << std::endl;
    std::cout << "Items: " << player.current_room->chest.listItems() << std::endl;
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
        player.setCurrentRoom(next_room);
        std::cout << player.current_room->getLongDescription() << std::endl;
    } else {
        std::cout << "The room you want to enter is locked" << std::endl;
    }
}

void Game::useItem(Command command) {
    if (!command.hasItem()) {
        std::cout << "What item?" << std::endl;
        return;
    } else if (!command.hasValidItem()) {
        std::cout << "That is not a valid item!" << std::endl;
        return;
    }

    UseContext ctx{};

    if (command.item == ItemType::Key) {
        if (!command.hasDirection()) {
            std::cout << "Use where?" << std::endl;
            return;
        } else if (!command.hasValidDirection()) {
            std::cout << "That is not a valid direction!" << std::endl;
            return;
        }

        Direction direction = command.direction;
        ctx.direction = direction;
    }

    ItemType item_type = command.item;

    Item* item = player.backpack.get(item_type);
    if (item != nullptr) {
        Player* player_pointer = &player;
        ctx.player = player_pointer;
        item->use(ctx);
        return;
    }

    std::cout << "The item was not found in your backpack!" << std::endl;
}

void Game::takeItem(Command command) {
    if (!command.hasItem()) {
        std::cout << "What item?" << std::endl;
        return;
    } else if (!command.hasValidItem()) {
        std::cout << "That is not a valid item!" << std::endl;
        return;
    }

    ItemType item_type = command.item;

    player.takeFromChest(item_type);
}

void Game::dropItem(Command command) {
    if (!command.hasItem()) {
        std::cout << "What item?" << std::endl;
        return;
    } else if (!command.hasValidItem()) {
        std::cout << "That is not a valid item!" << std::endl;
        return;
    }

    ItemType item_type = command.item;

    player.dropToChest(item_type);
}

void Game::createRooms() {
    unsigned int seed = time(nullptr);
    // unsigned int seed = 1783618278; // Fun map :)!
    srand(seed);
    std::cerr << seed << std::endl;
    MapGenerator map_generator = MapGenerator(seed, 6, 4);
    player.setCurrentRoom(map_generator.generate());
}

bool Game::processCommand(Command command) {
    bool wantToQuit = false;

    switch (command.type) {
        case CommandType::Help: {
            printHelp(command);
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
            MapView map_view(player.current_room);
            map_view.draw();
            break;
        }
        case CommandType::Use: {
            useItem(command);
            break;
        }
        case CommandType::Take: {
            takeItem(command);
            break;
        }
        case CommandType::Drop: {
            dropItem(command);
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
