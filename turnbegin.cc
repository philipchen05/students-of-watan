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

}

// Update player resources based on dice roll value
void TurnBegin::updateResources(int roll) {

}
