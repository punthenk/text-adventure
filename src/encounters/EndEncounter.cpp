/*
 * Copyright (c) 2026, Michiel Nijenhuis <contact@michielnijenhuis.com>
 *
 */

#include "EndEncounter.h"
#include "Command.h"
#include "CommandType.h"
#include "Game.h"
#include "core/Console.h"
#include "Player.h"

class Game;

EndEncounter::EndEncounter() { }

void EndEncounter::onStart(Player &player) {
}

bool EndEncounter::isActive() const {
    return is_active;
}


void EndEncounter::runRound(Player &player) {
    Console::typeLine("You enter a large control room.");
    Console::typeLine("In the center stands a large terminal surrounded by three card readers.");
    Console::typeLine("A big red message flashes across the screen:\n");
    Console::typeDangerLine("   FACILITY LOCKDOWN ACTIVE\n");
    Console::typeDangerLine("   THREE AUTHORIZATIONS REQUIRED\n");
    Console::typeLine("You notice three empty card slots.\n");
    Console::typeLine("Insert the cards (TIP: use the _ in the command. You know the command, i'm sure :)");
    

    Command command = parser.getEndCommand();
    while (command.end_command != EndCommand::InsertKeycards) {
        Console::typeWarningLine("You entered the wrong command. Insert the keycards");
        command = parser.getEndCommand();
    }

    Console::typeLine("You insert the first keycard.\n");
    Console::typeSuccessLine("ACCESS GRANTED.\n");
    Console::typeLine("You insert the second keycard.\n");
    Console::typeSuccessLine("ACCESS GRANTED.\n");
    Console::typeLine("You insert the third keycard.\n");
    Console::typeWarningLine("...\n");
    Console::typeSuccessLine("ALL AUTHORIZATIONS VERIFIED.\n");
    Console::typeWarningLine("WARNING:");
    Console::typeLine("MANUAL FACILITY OVERRIDE INITIATED.\n");
    Console::typeLine("ESTIMATED TIME TO LOCKDOWN:");
    Console::typeLine("5 SECONDS\n");

    const PromtEvent disable_security_event {
        "disable_security",
        "You need to disable the security system NOW! Type the command! I know you know it!",
        "SECURITY SYSTEM DISABLED.",
        "INVALID COMMAND.\n\n SECURITY SYSTEM HAS LOCKED YOU OUT.\n\n RETRYING...\n",
    };

    Console::typeLine(disable_security_event.explanation_message);

    string string_command = parser.getEndCommandStringWithTimeout(5);
    while (string_command.empty() || string_command != disable_security_event.required_command) {
        Console::typeDangerLine(disable_security_event.failure_message);
        string_command = parser.getEndCommandStringWithTimeout(5);
    }

    Console::typeSuccessLine(disable_security_event.success_message);

    Console::typeSuccessLine("You can escape the Facility!");
    Console::typeLine("Try to escape.");
    string_command = parser.getEndCommandString();
    while (string_command.empty() || string_command != "escape") {
        Console::typeDangerLine("Try again");
        string_command = parser.getEndCommandString();
    }

    Console::typeLine("YES! You escaped. Well done! Bye!");
    Game::stop();
}
