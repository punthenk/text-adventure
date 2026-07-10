/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "Game.h"
#include <iostream>
#include "Canvas.h"
#include "Command.h"
#include "CommandType.h"
#include "items/Knife.h"
#include "MapGenerator.h"
#include "MapView.h"
#include "core/Console.h"

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
    Console::printLine("Bye");
}

void Game::printHelp(Command command) {
    if (!command.hasItem()) {
        Console::printLine("Here is you help!");
        Console::printLine("(TIP: You can do `help item` to get more info about that item!)");
        parser.printValidCommands();
        return;
    } else if (!command.hasValidItem()) {
        Console::printLine("We don't support help for that item");
        return;
    }

    Console::printLine("ITEM HELP");
    Console::printLine("------------------------");

    Item* item = player.backpack.get(command.item);
    if (item != nullptr) {
        Console::printLine("Name: " + CommandLibrary::itemToString(item->getName()));
        Console::printLine("Description: " + item->getDescription());
        Console::printLine("Guide: " + item->getUseGuide());
        Console::printLine("Weight: " + std::to_string(item->getWeight()));
    } else {
        Console::printLine("You need to have that item in your backpack to ask help");
    }
}

void Game::status() {
    Console::printLine("Your health is " + std::to_string(player.getHealth()) + "/100");
    Console::printLine("----------------------");
    Console::printLine("Your inventory: " + player.backpack.listItems());
}

void Game::look() {
    Console::printLine(player.current_room->getLongDescription());
    Console::printLine("Items: " + player.current_room->chest.listItems());
}

void Game::goRoom(Command command) {
    if (!command.hasDirection()) {
        Console::printLine("Go where?");
        return;
    } else if (!command.hasValidDirection()) {
        Console::printLine("That is not a valid direction!");
        return;
    }

    Direction dir = command.direction;

    Room* next_room = player.current_room->getExit(dir);
    if (next_room == nullptr) {
        Console::printLine("There is not exit found in that direction!");
        return;
    }

    if (!next_room->getIsLocked()) {
        player.setCurrentRoom(next_room);
        player.damage(10);
        Console::printLine(player.current_room->getLongDescription());
    } else {
        Console::printLine("The room you want to enter is locked");
    }
}

void Game::useItem(Command command) {
    if (!command.hasItem()) {
        Console::printLine("What item?");
        return;
    } else if (!command.hasValidItem()) {
        Console::printLine("That is not a valid item!");
        return;
    }

    Item* item = player.backpack.get(command.item);
    UseContext ctx{};

    if (item == nullptr) {
        Console::printLine("The item was not found in your backpack!");
        return;
    }

    if (command.item == ItemType::Key) {
        if (!command.hasDirection()) {
            Console::printLine("Use where?");
            return;
        } else if (!command.hasValidDirection()) {
            Console::printLine("That is not a valid direction!");
            return;
        }

        Direction direction = command.direction;
        ctx.direction = direction;
    }


    Player *player_pointer = &player;
    ctx.player = player_pointer;
    item->use(ctx);

    // FIXME: Item deleted when not used successfully
    if (item->isOneTimeUse()) {
        player.backpack.removeItem(command.item);
        delete item;
    }
}

void Game::takeItem(Command command) {
    if (!command.hasItem()) {
        Console::printLine("What item?");
        return;
    } else if (!command.hasValidItem()) {
        Console::printLine("That is not a valid item!");
        return;
    }

    ItemType item_type = command.item;

    player.takeFromChest(item_type);
}

void Game::dropItem(Command command) {
    if (!command.hasItem()) {
        Console::printLine("What item?");
        return;
    } else if (!command.hasValidItem()) {
        Console::printLine("That is not a valid item!");
        return;
    }

    ItemType item_type = command.item;

    player.dropToChest(item_type);
}

void Game::createRooms() {
    // unsigned int seed = time(nullptr);
    unsigned int seed = 1783697259; // Fun map :)!
    srand(seed);
    std::cerr << seed << std::endl;
    MapGenerator map_generator = MapGenerator(seed, 15, 10);
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
            Console::printLine("I have no clue what you want...");
            break;
        }
        default: {
            Console::printLine("I have no clue what you want...");
        }
    }

    return wantToQuit;
}
