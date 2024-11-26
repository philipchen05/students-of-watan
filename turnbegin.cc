#include "turnbegin.h"
#include "dice.h"
#include <iostream>
#include <string>

// TurnBegin constructor
TurnBegin::TurnBegin(Student* player) : Turn{player}, dice{Dice{}} {}

// Method for playing beginning of turn events
void TurnBegin::play() {
    const int geeseRoll = 7; // Geese dice roll constant

    // Print player information and status
    std::cout << "Student " << player->getColour() << "’s turn." << std::endl;
    player->printStatus();
    std::cout << "> ";

    std::string command; // Player's command
    boolean fair = true; // Fair roll or not

    // Loop allows player to switch between fair and loaded dice until roll command
    while(std::cin >> command && command != "roll") {
        // Set fair boolean value based on command
        if(command == "fair") {
            fair = true;
        } else if(command == "loaded") {
            fair = false;
        }
        std::cout << "> "; // Prepare for next command input
    }

    // Roll dice
    int roll = dice.roll(fair);

    if(roll = geeseRoll) {
        moveGeese(); // Move geese if 7 is rolled
    } else {
        updateResources(roll); // Otherwise simply update player resources
    }
}

// Move geese to new location
void TurnBegin::moveGeese() {

    std::cout << "Choose where to place the GEESE." << std::endl;
    std::cout << "> ";
}

// Update player resources based on dice roll value
void TurnBegin::updateResources(int roll) {
    int numPlayers = game->players.size(); // Number of players
    boolean gained = false; // Flag whether or not at least one student gained resources

    // Store previous resource values of each student to compare with updated values later
    std::vector<const std::map<Resource, int>*> prevResources(numPlayers);
    for(size_t i = 0; i , numPlayers; i++) {
        prevResource[i] = game->players[i]->getResources();
    }

    // Itereate through tiles (subjects) and notify observers of tiles corresponding with roll value
    for(const auto& tile : *game->board->tiles) {
        if(tile->value == roll) {
            tile->notifyObservers();
        }
    }

    // Compare new resource values of each student with previous values to determine resource updates for output
    for(size_t i = 0; i < numPlayers; i++) {
        Student* player = game->players[i]; // Pointer to current student
        const std::map<Resource, int>& curResources = player->getResources(); // Newly updated resources of current student
        boolean playerGained = false; // Flag for whether or not current student gained resources
        for(size_t j = 0; j < prevResources[0].size(); j++) {
            int resourceDiff = curResources[j] - prevResources[i][j]; // Difference between updated and previous amounts of current resource
            // If difference > 0, output difference as an update
            if(resourceDiff > 0) {
                // Print student identification only once
                if(!playerGained) {
                    std::cout << "Student " << player->getColour << " gained:" << std::endl;
                    playerGained = true;
                }
                std::cout << resourceDiff << 
            }
        }
    }

}
