#include "turnbegin.h"
#include "tile.h"
#include "game.h"
#include <iostream>
#include <string>
#include <random>

// TurnBegin constructor
TurnBegin::TurnBegin(Game* game, Student* player, std::mt19937 &gen) : Turn{game, player}, dice{Dice{gen}}, gen{gen} {}

// Method for playing beginning of turn events
void TurnBegin::play() {
    const int geeseRoll = 7; // Geese dice roll constant

    // Print player information and status
    std::cout << "Student " << player->getColour() << "’s turn." << std::endl;
    player->printStatus();
    std::cout << "> ";

    std::string command; // Player's command
    bool fair = true; // Fair roll or not

    // Loop allows player to switch between fair and loaded dice until roll command
    while(std::cin >> command && command != "roll") {
        // Set fair boolean value based on command
        if(command == "fair") {
            fair = true;
        } else if(command == "load") {
            fair = false;
        } else {
            std::cout << "Invalid command." << std::endl;
        }
        std::cout << "> "; // Prepare for next command input
    }
    if (std::cin.eof()) throw std::invalid_argument{"EOF"};

    // Roll dice
    int roll = dice.roll(fair);

    if(roll == geeseRoll) {
        moveGeese(); // Move geese if 7 is rolled
    } else {
        updateResources(roll); // Otherwise simply update player resources
    }
}

// Move geese to new location
void TurnBegin::moveGeese() {
    const int numPlayers = game->getNumPlayers(); // Number of players
    const int geeseMin = 10; // Minimum number of total resources for geese to be able to "steal" from a player
    std::vector<int> amountsLost; // Resource amounts lost in player index order

    // Store previous resource values of each student to compare with updated values later
    std::vector<std::map<Resource, int>> prevResources(numPlayers);
    for(int i = 0; i < numPlayers; i++) {
        prevResources[i] = game->getPlayer(i)->getResources();
    }

    // Each player with more than 10 total resources randomly loses half
    for(int i = 0; i < numPlayers; i++) {
        Student* s = game->getPlayer(i); // Pointer to current player
        int totalResources = s->getTotalResources(); // Current player's total resources
        if(totalResources >= geeseMin) {
            int numLost = totalResources / 2;
            amountsLost.push_back(numLost);
            for(int i = 0; i < numLost; i++) {
                loseResource(*s);
            }
        }
    }

    printLosses(prevResources, &amountsLost); // Print all resource losses

    int newGeeseLocation; // New geese tile location
    Tile* newGeeseTile; // Pointer to tile with new geese location
    std::vector<Student*> stealableStudents; // Students that can be stolen from
    std::cout << "Choose where to place the GEESE." << std::endl; // Prompt player for new geese location
    std::cout << "> ";
    std::cin >> newGeeseLocation;
    if (std::cin.eof()) throw std::invalid_argument{"EOF"};

    newGeeseTile = game->getBoard()->getTiles()[newGeeseLocation].get();

    // Determine stealable students by iterating through all students one by one
    for(int i = 0; i < numPlayers; i++) {
        Student* s = game->getPlayer(i); // Pointer to current player
        if(s != player) { // Skip the student who currently has their turn
            // Iterate through each criteria on the new geese tile to see if any are owner by the current student
            for(const auto& c : newGeeseTile->getCriteria()) {
                if(c->getOwnerName() == s->getColour()) {
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
        std::cout << "Student " << player->getColour() << " has no students to steal from." << std::endl; // No students available to steal from
    } else {
        // Print stealable students
        std::cout << "Student " << player->getColour() << " can choose to steal from ";
        for(int i = 0; i < numStealable; i++) {
            std::cout << stealableStudents[i]->getColour();
            if(i < numStealable - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "." << std::endl;

        // Prompt player for who to steal from
        std::string victimColour;
        Student* victim;
        std::cout << "Choose a student to steal from." << std::endl;
        std::cout << "> ";
        std::cin >> victimColour;
        victimColour = formatName(victimColour); // Properly format colour capitalization
        if (std::cin.eof()) throw std::invalid_argument{"EOF"};


        // Set pointer to victim student (student who is stolen from)
        for(const auto& s : stealableStudents) {
            if(s->getColour() == victimColour) {
                victim = s;
            }
        }

        Resource resource = loseResource(*victim); // Stolen resource
        player->addResources(resource, 1); // Add stolen resource to current player
        
        // Output update on stolen resource
        std::cout << "Student " << player->getColour() << " steals " << resource << " from student " << victim->getColour() << "." << std::endl;
    }

    Tile* prevGeeseLocation = game->getBoard()->getGeeseLocation(); // Pointer to tile with previous geese location
    if(prevGeeseLocation) {
        prevGeeseLocation->setGeese(false); // Set tile with previous geese location to no longer have geese
    }
    newGeeseTile->setGeese(true); // Set geese to be true on new geese tile
}

// Update player resources based on dice roll value
void TurnBegin::updateResources(int roll) {
    const int numPlayers = game->getNumPlayers(); // Number of players
    const std::string playerMessage = " gained:";

    // Store previous resource values of each student to compare with updated values later
    std::vector<std::map<Resource, int>> prevResources(numPlayers);
    for(int i = 0; i < numPlayers; i++) {
        prevResources[i] = game->getPlayer(i)->getResources();
    }
    std::cerr << "got prev resources" << std::endl; // DEBUG - MUST DELETE

    // Itereate through tiles (subjects) and notify observers of tiles corresponding with roll value that don't have geese
    for(const auto& tile : game->getBoard()->getTiles()) {
        if(tile->getValue() == roll && !tile->hasGeese()) {
            std::cerr << "notifying tile" << *tile << std::endl; // DEBUG - MUST DELETE
            tile->notifyObservers();
        }
    }
    std::cerr << "notified all tiles" << std::endl; // DEBUG - MUST DELETE

    if(!printUpdates(prevResources, 1, nullptr)) {
        std::cout << "No students gained resources." << std::endl; // Output if no students gained resources
    }
}

// Output resource updates; returns true if at least one resource updated
bool TurnBegin::printUpdates(std::vector<std::map<Resource, int>> &prevResources, bool gain, std::vector<int>* amountsLost) const {
    std::cerr << "in printUpdates" << std::endl; // DEBUG - MUST DELETE
    int numPlayers = game->getNumPlayers(); // Number of players
    std::vector<Resource> resources = {Resource::CAFFEINE, Resource::LAB, Resource::LECTURE, Resource::STUDY, Resource::TUTORIAL}; // Stores resources in output order
    bool update = false; // Flag whether or not at least one student's resources were updated
    int lostIndex = 0; // Index for amountsLost vector

    // Compare new resource values of each student with previous values to determine resource updates for output
    for(int i = 0; i < numPlayers; i++) {
        Student* player = game->getPlayer(i); // Pointer to current student
        std::cerr << "student " << player->getColour() << std::endl; // DEBUG - MUST DELETE
        const std::map<Resource, int>& curResources = player->getResources(); // Newly updated resources of current student
        bool playerUpdated = false; // Flag for whether or not current student resources were updated
        for(size_t j = 0; j < resources.size(); j++) {
            Resource curResource = resources[j]; // Current resource
            int resourceDiff = abs(curResources.at(curResource) - prevResources[i].at(curResource)); // Difference between updated and previous amount of current resource
            // If difference > 0, output difference as an update
            if(resourceDiff > 0) {
                // Print student identification message only once
                if(!playerUpdated) {
                    std::cout << "Student " << player->getColour();
                    if(gain) {
                        std::cout << " gained:";
                    } else {
                        std::cout << " loses " << (*amountsLost)[lostIndex++] << " resources to the geese. They lose:";
                    }
                    std::cout << std::endl;
                    playerUpdated = true;
                }
                std::cout << resourceDiff << " " << curResource << std::endl; // Output resource update amount
                update = true;
            }
        }
    }

    return update; // Return whether or not an update occurred
}

// Output resource gains; returns true if at least one resource was gained
bool TurnBegin::printGains(std::vector<std::map<Resource, int>> &prevResources) const {
    return printUpdates(prevResources, 1, nullptr);
}

// Output resource losses; returns true if at least one resource was lost
bool TurnBegin::printLosses(std::vector<std::map<Resource, int>> &prevResources, std::vector<int>* amountsLost) const {
    return printUpdates(prevResources, 0, amountsLost);
}

// Loses one random resource for given Student and returns it; proportional probabilities of losing each resource
Resource TurnBegin::loseResource(Student& s) {
    std::vector<Resource> resourceOrder = {Resource::CAFFEINE, Resource::LAB, Resource::LECTURE, Resource::STUDY, Resource::TUTORIAL}; // Order of resources
    const size_t numResources = resourceOrder.size(); // Total number of distinct resources
    Resource resource; // Resource lost
    std::uniform_int_distribution<> distrib{1, s.getTotalResources()}; // Range between 1 and total number of resources for proportional probabilities
    const std::map<Resource, int>& resources = s.getResources(); // Student's resources
    std::vector<int> prefixSum(numResources); // Prefix sum array of Student resource amounts (order is CAFFEINE, LAB, LECTURE, STUDY, TUTORIAL)
    
    // Initialize prefix sum array values
    int sum = 0;
    for(size_t i = 0; i < numResources; i++) {
        sum += resources.at(resourceOrder[i]);
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
