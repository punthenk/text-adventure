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
    // printWelcome();

    while (!finished && player.isAlive()) {
        Command command = parser.getCommand();
        finished = processCommand(command);
    }
    Console::typeLine("Bye", 50);
}

void Game::printWelcome() {
    Console::typeLine("Welcome to the text-adventure game 'The Facility'");
    Console::typeLine("This is going to be an incredible !boring game ;)");
    Console::typeLine("To begin, type `help` if you need any help");
    Console::typeLine("You goal is to exit the facility and survive!");
    Console::typeLine("GOOD LUCK!\n");
    Console::typeLine(player.current_room->getDescription());
}

void Game::printHelp(Command command) {
    if (!command.hasItem()) {
        Console::printLine("Here is you help!");
        Console::printLine("(TIP: You can do `help item` to get more info about that item!)");
        parser.printValidCommands();
        return;
    } else if (!command.hasValidItem()) {
        Console::printWarningLine("We don't support help for that item");
        return;
    }

    Console::printSuccessLine("ITEM HELP");
    Console::printLine("------------------------");

    Item* item = player.backpack.get(command.item);
    if (item != nullptr) {
        Console::printInfo("Name: ");
        Console::printSuccessLine(CommandLibrary::itemToString(item->getName()));
        Console::printInfo("Description: ");
        Console::printSuccessLine(item->getDescription());
        Console::printInfo("Guide: ");
        Console::printSuccessLine(item->getUseGuide());
        Console::printInfo("Weight: ");
        Console::printSuccessLine(std::to_string(item->getWeight()));
    } else {
        Console::printWarningLine("You need to have that item in your backpack to ask help");
    }
}

void Game::status() {
    Console::printInfo("Your health is ");
    Console::printSuccessLine(std::to_string(player.getHealth()) + "/100");
    Console::printLine("----------------------");
    Console::printInfo("Your inventory: ");
    Console::printSuccessLine(player.backpack.listItems());
}

void Game::look() {
    Console::printLine("You are " + player.current_room->getDescription());
    Console::printInfo("Exits: ");
    Console::printWarningLine(player.current_room->getExitString());
    Console::printInfo("Items: ");
    Console::printSuccessLine(player.current_room->chest.listItems());
}

void Game::goRoom(Command command) {
    if (!command.hasDirection()) {
        Console::printWarningLine("Go where?");
        return;
    } else if (!command.hasValidDirection()) {
        Console::printWarningLine("That is not a valid direction!");
        return;
    }

    Direction dir = command.direction;

    Room* next_room = player.current_room->getExit(dir);
    if (next_room == nullptr) {
        Console::printWarningLine("There is no exit found in that direction!");
        return;
    }

    if (!next_room->getIsLocked()) {
        player.setCurrentRoom(next_room);
        player.damage(10);
        Console::typeLine(player.current_room->getDescription());
        Console::printInfo("Exits: ");
        Console::printSuccessLine(player.current_room->getExitString());
        Console::printInfo("Items: ");
        Console::printSuccessLine(player.current_room->chest.listItems());
    } else {
        Console::printWarningLine("The room you want to enter is locked");
    }
}

void Game::useItem(Command command) {
    if (!command.hasItem()) {
        Console::printWarningLine("What item?");
        return;
    } else if (!command.hasValidItem()) {
        Console::printWarningLine("That is not a valid item!");
        return;
    }

    Item* item = player.backpack.get(command.item);

    if (item == nullptr) {
        Console::printWarningLine("The item was not found in your backpack!");
        return;
    }

    UseContext ctx{};

    if (command.hasDirection())
        ctx.direction = command.direction;

    ctx.player = &player;

    bool use_success = item->use(ctx);

    if (use_success && item->isOneTimeUse())
        player.backpack.remove(command.item);
}

void Game::takeItem(Command command) {
    if (!command.hasItem()) {
        Console::printWarningLine("What item?");
        return;
    } else if (!command.hasValidItem()) {
        Console::printWarningLine("That is not a valid item!");
        return;
    }

    ItemType item_type = command.item;

    player.takeFromChest(item_type);
}

void Game::dropItem(Command command) {
    if (!command.hasItem()) {
        Console::printWarningLine("What item?");
        return;
    } else if (!command.hasValidItem()) {
        Console::printWarningLine("That is not a valid item!");
        return;
    }

    player.dropToChest(command.item);
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
            Console::printWarningLine("I have no clue what you want...");
            break;
        }
        default: {
            Console::printWarningLine("I have no clue what you want...");
        }
    }

    return wantToQuit;
}
