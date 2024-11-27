#include "turnend.h"
#include <string>
#include <iostream>
#include <fstream>

// TurnBegin constructor
TurnEnd::TurnEnd(Student* player) : Turn{player} {}

// Method for playing end of turn events
void TurnEnd::play() {
    string command; // Player's command
    std::cout >> "> ";
    std::cin >> command;

    // Execute player commands until "next" command
    while(command != "next") {
        switch(command) {
            case "board":
                board();
                break;
            case "status":
                status();
                break;
            case "criteria":
                criteria();
                break;
            case "achieve":
                int id; // Goal id
                std::cin >> id;
                achieve(id);
                break;
            case "complete":
                int id; // Criterion id
                std::cin >> id;
                complete(id);
                break;
            case "improve":
                int id; // Criterion id
                std::cin >> id;
                improve(id);
                break;
            case "trade":
                string colour, give, take;
                std::cin >> colour >> give >> take;
                trade(colour, give, take);
                break;            
            case "save":
                string file;
                std::cin >> file;
                save(file);
                break;
            case "help":
                help();
                break;
            default:
                std::cout << "Invalid command."
        }
        std::cout << "> ";
        std::cin >> command;
    }
}

// Display board
void TurnEnd::board() {
    game->board->display();
}

// Print status of each student in order of student index
void TurnEnd::status() {
    for(const auto& s : game->players) {
        s->printStatus();
    }
}

// Print current student's criteria
void TurnEnd::criteria() {
    s->printCriteria(); 
}

// Determine if player can afford desired goal/achievement
bool TurnEnd::canAfford(Achievement* a) {
    const std::map<Resource, int>& upgradeCost = a->getUpgradeCost(); // Upgrade cost
    const std::map<Resource, int>& resources = player->getResources(); // Player resources
    for(const auto& [resource, cost] : upgradeCost) {
        if(cost > resources[resource]) {
            return false; // Return false if player does not have enough of a given resource
        }
    }
    return true; // Return true if no lack of resources found
}

// Deducts cost of given achievement from player resources
void TurnEnd::purchase(Achievement* a) {
    const std::map<Resource, int>& upgradeCost = a->getUpgradeCost(); // Upgrade cost
    const std::map<Resource, int>& resources = player->getResources(); // Player resources
    for(const auto& [resource, cost] : upgradeCost) {
        player->removeResources(resource, cost); // Deduct resource
    }
}

// Achieve goal
void TurnEnd::achieve(int id) {
    Goal* goal = game->board->getGoals()[id]; // Pointer to goal

    // Check if space is valid
    if(!game->board->canBuildGoal(id, *player)) {
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
    Criterion* criterion = game->board->getCriteria()[id]; // Pointer to criterion

    // Check if space is valid
    if(!game->board->canBuildCriterion(id, *player)) {
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
    Criterion* criterion = game->board->getCriteria()[id]; // Pointer to criterion

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
void TurnEnd::trade(string colour, string give, string take) {
    Student* otherPlayer; // Pointer to other player
    Resource resource1 = resource(give); // Resource being offered
    Resource resource2 - resource(take); // Resource wanted in return

    // Determine otherPlayer
    for(const auto& s : game->players) {
        if(s->getColour() == colour) {
            otherPlayer = s;
            break;
        }
    }

    // Prompt other player with trade proposition
    std::cout << player-getColour() << " offers " << otherPlayer.getColour() << " one " << resource1 << " for one " << resource2 << "." << std::endl;
    std::cout << "Does " otherPlayer->getColour() << " accept this offer?" << std::endl;

    string response; // Other player's response
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
    ofstream out{file}; // Output file stream
    out << player->getColour() << std::endl;
    for(const auto& s : game->players) {
        out << s->getData() << std::endl;
    }
    out << game->board->getData() << std::endl;
    out << game->board->getGeeseLocation()->getLocation() << std::endl;
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
