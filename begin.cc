#include "begin.h"
#include <iostream>
#include <string>

// Begin constructor
Begin::Begin(Game* game) : GamePhase{game} {}

// Method for executing beginning of game events
void Begin::play() {
    int numTurns = game->players.size() * 2; // Total number of turns in beginning of game

    // Prompt students for starting assignment location; first in order, then in reverse-order
    for(size_t i = 0; i < numTurns; i++) {
        int index = numTurns > 3 ? numTurns - 1 - i : i; // Calculate index number of player whose turn it is to choose an assignment
        int intersection; // Stores player input for desired intersection
        Student* player = game->players[index]; // Current student

        // Prompt player for input
        std::cout << "Student " << player->colour << ", where do you want to complete an Assignment?" << std::endl;
        std::cout << "> ";

        // Handle invalid intersections
        while(std::cin >> intersection && !game->board->isValid(intersection)) {
            std::cout << "You cannot build here." << endl;
            std::cout << "> ";
        }
        
        game->board->sortedCriteria[intersection]->complete(player);
    }

    // Print updated board
}
