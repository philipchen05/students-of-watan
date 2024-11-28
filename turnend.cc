#include "turnend.h"
#include "game.h"
#include <string>
#include <iostream>
#include <fstream>

// TurnBegin constructor
TurnEnd::TurnEnd(Game* game, Student* player) : Turn{game, player} {}

// Method for playing end of turn events
void TurnEnd::play() {
    std::string command; // Player's command
    std::cout << "> ";
    std::cin >> command;

    // Execute player commands until "next" command
    while(command != "next") {
        if(command == "board") {
            board();
        } else if(command == "status") {
            status();
        } else if(command == "criteria") {
            criteria();
        } else if(command == "achieve") {
            int id; // Goal id
            std::cin >> id;
            achieve(id);
        } else if(command == "complete") {
            int id; // Criterion id
            std::cin >> id;
            complete(id);
        } else if(command == "improve") {
            int id; // Criterion id
            std::cin >> id;
            improve(id);
        } else if(command == "trade") {
            std::string colour, give, take;
            std::cin >> colour >> give >> take;
            trade(colour, give, take);
        } else if(command == "save") {
            std::string file;
            std::cin >> file;
            save(file);
        } else if(command == "help") {
            help();
        } else {
            std::cout << "Invalid command.";
        }
        std::cout << "> ";
        std::cin >> command;
    }
}

// Display board
void TurnEnd::board() {
    game->getBoard()->display();
}

// Print status of each student in order of student index
void TurnEnd::status() {
    for(int i = 0; i < game->getNumPlayers(); i++) {
        Student* s = game->getPlayer(i); // Pointer to current student
        s->printStatus();
    }
}

// Print current student's criteria
void TurnEnd::criteria() {
    player->printCriteria(); 
}

// Determine if player can afford desired goal/achievement
bool TurnEnd::canAfford(Achievement* a) {
    const std::map<Resource, int>& upgradeCost = a->getUpgradeCost(); // Upgrade cost
    const std::map<Resource, int>& resources = player->getResources(); // Player resources
    for(const auto& [resource, cost] : upgradeCost) {
        if(cost > resources.at(resource)) {
            return false; // Return false if player does not have enough of a given resource
        }
    }
    return true; // Return true if no lack of resources found
}

// Deducts cost of given achievement from player resources
void TurnEnd::purchase(Achievement* a) {
    const std::map<Resource, int>& upgradeCost = a->getUpgradeCost(); // Upgrade cost
    for(const auto& [resource, cost] : upgradeCost) {
        player->removeResources(resource, cost); // Deduct resource
    }
}

// Achieve goal
void TurnEnd::achieve(int id) {
    Goal* goal = game->getBoard()->getGoals()[id].get(); // Pointer to goal

    // Check if space is valid
    if(!game->getBoard()->canBuild(id, *player)) {
        std::cout << "You cannot build here." << std::endl;
        return;
    }

    // Check if player has enough resources
    if(!canAfford(goal)) {
        std::cout << "You do not have enough resources." << std::endl; // Output if player doesn't have enough of a resource
        return;
    }

    // Achieve goal and deduct cost from player resources
    goal->achieve(player);
    player->addGoal(goal);
    purchase(goal);
}

// Complete criterion
void TurnEnd::complete(int id) {
    Criterion* criterion = game->getBoard()->getCriteria()[id].get(); // Pointer to criterion

    // Check if space is valid
    if(!game->getBoard()->canBuild(id, *player)) {
        std::cout << "You cannot build here." << std::endl;
        return;
    }

    // Check if player has enough resources
    if(!canAfford(criterion)) {
        std::cout << "You do not have enough resources." << std::endl; // Output if player doesn't have enough of a resource
        return;
    }

    // Complete criterion and deduct cost from player resources
    criterion->complete(player);
    player->addCriterion(criterion);
    purchase(criterion);
}

// Improve criterion
void TurnEnd::improve(int id) {
    Criterion* criterion = game->getBoard()->getCriteria()[id].get(); // Pointer to criterion

    // Check if space is valid
    if(criterion->getOwnerName() == player->getColour()) {
        std::cout << "You cannot build here." << std::endl;
        return;
    }

    // Check if player has enough resources
    if(!canAfford(criterion)) {
        std::cout << "You do not have enough resources." << std::endl; // Output if player doesn't have enough of a resource
        return;
    }

    // Improve criterion and deduct cost from player resources
    criterion->improve();
    purchase(criterion);
}

// Trade resources with another player
void TurnEnd::trade(std::string colour, std::string give, std::string take) {
    Student* otherPlayer; // Pointer to other player
    Resource resource1 = resourceFromString(give); // Resource being offered
    Resource resource2 = resourceFromString(take); // Resource wanted in return

    // Determine otherPlayer
    for(int i = 0; i < game->getNumPlayers(); i++) {
        Student* s = game->getPlayer(i); // Pointer to current player
        if(s->getColour() == colour) {
            otherPlayer = s;
            break;
        }
    }

    // Prompt other player with trade proposition
    std::cout << player->getColour() << " offers " << otherPlayer->getColour() << " one " << resource1 << " for one " << resource2 << "." << std::endl;
    std::cout << "Does " << otherPlayer->getColour() << " accept this offer?" << std::endl;

    std::string response; // Other player's response
    std::cout << "> ";
    std::cin >> response;

    // Make trade if other player agrees
    if(response == "yes") {
        player->removeResources(resource1, 1);
        player->addResources(resource2, 1);
        otherPlayer->removeResources(resource2, 1);
        otherPlayer->addResources(resource1, 1);
    }
}

// Saves current game state to specified file
void TurnEnd::save(std::string file) {
    std::ofstream out{file}; // Output file stream
    out << player->getColour() << std::endl;
    for(int i = 0; i < game->getNumPlayers(); i++) {
        Student* s = game->getPlayer(i); // Pointer to current player
        out << s->getData() << std::endl;
    }
    //out << game->getBoard()->getData() << std::endl;
    out << game->getBoard()->getGeeseLocation()->getLocation() << std::endl;
    out.close();
}

// Print help guide
void TurnEnd::help() {
    std::cout << "Valid commands:" << std::endl;
    std::cout << "board" << std::endl;
    std::cout << "status" << std::endl;
    std::cout << "criteria" << std::endl;
    std::cout << "achieve <goal>" << std::endl;
    std::cout << "complete <criterion>" << std::endl;
    std::cout << "improve <criterion>" << std::endl;
    std::cout << "trade <colour> <give> <take>" << std::endl;
    std::cout << "next" << std::endl;
    std::cout << "save <file>" << std::endl;
    std::cout << "help" << std::endl;
}
