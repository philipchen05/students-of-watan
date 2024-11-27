#include "turnbegin.h"
#include <iostream>
#include <string>
#include <random>

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
        } else {
            std::cout << "Invalid command." << std::endl;
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
    const int geeseMin = 10; // Minimum number of total resources for geese to be able to "steal" from a player
    std::vector<int> amountsLost; // Resource amounts lost in player index order

    // Store previous resource values of each student to compare with updated values later
    std::vector<const std::map<Resource, int>*> prevResources(numPlayers);
    for(size_t i = 0; i < numPlayers; i++) {
        prevResources[i] = game->players[i]->getResources();
    }

    // Each player with more than 10 total resources randomly loses half
    for(const auto& s : game->players) {
        int totalResources = s->getTotalResources(); // Current player's total resources
        if(totalResources >= geeseMin) {
            int numLost = totalResources - (totalResources / 2)
            amountsLost.push_back(numLost);
            for(int i = 0; i < numLost; i++) {
                loseResource(*s);
            }
        }
    }

    printLosses(prevResources, &amountsLost); // Print all resource losses

    int newGeeseLocation; // New geese tile location
    Tile* newGeeseTile; // Pointer to tile with new geese location
    std::vector<const Student*> stealableStudents; // Students that can be stolen from
    std::cout << "Choose where to place the GEESE." << std::endl; // Prompt player for new geese location
    std::cout << "> ";
    std::cin >> newGeeseLocation;
    newGeeseTile = (*game->board->tiles)[newGeeseLocation];

    // Determine stealable students by iterating through all students one by one
    for(const auto& s : game->players) {
        if(s != player) { // Skip the student who currently has their turn
            // Iterate through each criteria on the new geese tile to see if any are owner by the current student
            for(Criterion* c : newGeeseTile->criteria) {
                if(c->owner == s) {
                    if(s->getTotalResources() > 0) {
                        stealableStudents.push_back(s); // Only mark student as stealable if they have more than 0 resources
                    }
                    break;
                }
            }
        }
    }

    // Steal from a student (if possible)
    int numStealable = stealableStudents.size(); // Number of stealable students
    if(numStealable == 0) {
        std::cout << "Student " player->getColour() << " has no students to steal from." << std::endl; // No students available to steal from
    } else {
        // Print stealable students
        std::cout << "Student " << s->getColour() << " can choose to steal from ";
        for(size_t i = 0; i < numStealable; i++) {
            std::cout << stealableStudents[i];
            if(i < numStealable - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "." << std::endl;

        // Prompt player for who to steal from
        string victimColour;
        Student* victim;
        std::cout << "Choose a student to steal from." << std::endl;
        std::cout << "> ";
        std::cin >> victimColour;

        // Set pointer to victim student (student who is stolen from)
        for(const auto& s : stealableStudents) {
            if(s->colour == victimColour) {
                victim = &s;
            }
        }

        Resource resource = loseResource(victim); // Stolen resource
        player->addResources(resource, 1); // Add stolen resource to current player
        
        // Output update on stolen resource
        std::cout << "Student " << player->getColour() << " steals " << resource << " from student " << victim.getColour() << "." << std::endl;
    }

    game->board->getGeeseLocation()->setGeese(false); // Set tile with current geese location to no longer have geese
    newGeeseTile->setGeese(true); // Set geese to be true on new geese tile
}

// Update player resources based on dice roll value
void TurnBegin::updateResources(int roll) {
    const int numPlayers = game->players.size(); // Number of players
    const string playerMessage = " gained:";

    // Store previous resource values of each student to compare with updated values later
    std::vector<const std::map<Resource, int>*> prevResources(numPlayers);
    for(size_t i = 0; i < numPlayers; i++) {
        prevResources[i] = game->players[i]->getResources();
    }

    // Itereate through tiles (subjects) and notify observers of tiles corresponding with roll value that don't have geese
    for(const auto& tile : *game->board->tiles) {
        if(tile->getValue() == roll && !tile->hasGeese()) {
            tile->notifyObservers();
        }
    }

    if(!printUpdates(prevResources, playerMessage)) {
        std::cout << "No students gained resources." << std::endl; // Output if no students gained resources
    }
}

// Output resource updates; returns true if at least one resource updated
boolean TurnBegin::printUpdates(std::vector<const std::map<Resource, int>*> &prevResources, boolean gain, std::vector<int>* amountsLost) const {
    int numPlayers = game->players.size(); // Number of players
    std::vector<Resource> resources = {Resource::CAFFEINE, Resource::LAB, Resource::LECTURE, Resource::STUDY, Resource::TUTORIAL}; // Stores resources in output order
    boolean update = false; // Flag whether or not at least one student's resources were updated
    int lostIndex = 0; // Index for amountsLost vector

    // Compare new resource values of each student with previous values to determine resource updates for output
    for(size_t i = 0; i < numPlayers; i++) {
        Student* player = game->players[i]; // Pointer to current student
        const std::map<Resource, int>& curResources = player->getResources(); // Newly updated resources of current student
        boolean playerUpdated = false; // Flag for whether or not current student resources were updated
        for(size_t j = 0; j < resources.size(); j++) {
            Resource curResource = resources[j]; // Current resource
            int resourceDiff = abs(curResources[curResource] - prevResources[i][curResource]); // Difference between updated and previous amount of current resource
            // If difference > 0, output difference as an update
            if(resourceDiff > 0) {
                // Print student identification message only once
                if(!playerUpdated) {
                    std::cout << "Student " << player->getColour;
                    if(gain) {
                        std::cout << " gained:"
                    } else {
                        std::cout << " loses " << (*amountsLost)[lostIndex++] << " resources to the geese. They lose:";
                    }
                    std::cout << std::endl;
                    playerUpdated = true;
                }
                std::cout << resourceDiff << curResource << std::endl; // Output resource update amount
                update = true;
            }
        }
    }

    return update; // Return whether or not an update occurred
}

// Output resource gains; returns true if at least one resource was gained
boolean TurnBegin::printGains(std::vector<const std::map<Resource, int>*> &prevResources) const {
    return printUpdates(prevResources, 1, nullptr);
}

// Output resource losses; returns true if at least one resource was lost
boolean TurnBegin::printLosses(std::vector<const std::map<Resource, int>*> &prevResources, std::vector<int>* amountsLost) const {
    return printUpdates(prevResources, 0, amountsLost);
}

// Loses one random resource for given Student and returns it; proportional probabilities of losing each resource
Resource TurnBegin::loseResource(const Student& s) {
    std::vector<Resource> resourceOrder = {Resource::CAFFEINE, Resource::LAB, Resource::LECTURE, Resource::STUDY, Resource::TUTORIAL}; // Order of resources
    const size_t numResources = resourceOrder.size(); // Total number of distinct resources
    Resource resource; // Resource lost
    std::random_device rd; // Generate non-deterministic seed
    std::mt19937 gen{rd()}; // Initialize random number generator with seed
    std::uniform_int_distribution<> distrib{1, s.getTotalResources()}; // Range between 1 and total number of resources for proportional probabilities
    const std::map<Resource, int>& resources = s.getResources(); // Student's resources
    std::vector<int> prefixSum(numResources); // Prefix sum array of Student resource amounts (order is CAFFEINE, LAB, LECTURE, STUDY, TUTORIAL)
    
    // Initialize prefix sum array values
    int sum = 0;
    for(size_t i = 0; i < numResources; i++) {
        sum += resources[resourceOrder[i]];
        prefixSum[i] = sum;
    }

    // Generate random number and map number to corresponding resource (resources partitioned by respective amounts)
    int n = distrib(gen);
    for (size_t i = 0; i < numResources; i++) {
        if (n <= prefixSum[i]) {
            resource = resourceOrder[i];
            break;
        }
    }

    // Remove resource and return it
    s.removeResources(resource, 1);
    return resource;
}
