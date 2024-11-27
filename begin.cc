#include "begin.h"
#include "gamephase.h"
#include "game.h"

#include <iostream>
#include <string>

// Begin constructor
Begin::Begin(Game* game) : GamePhase{game} {}

// Method for executing beginning of game events
void Begin::play() {
    const int numTurns = game->getNumPlayers() * 2; // Total number of turns in beginning of game
    Board* board = game->getBoard(); // Pointer to Board

    // Prompt students for starting assignment location; first in order, then in reverse-order
    for(size_t i = 0; i < numTurns; i++) {
        int index = numTurns > 3 ? numTurns - 1 - i : i; // Calculate index number of player whose turn it is to choose an assignment
        int intersection; // Stores player input for desired intersection
        Student* player = game->getPlayer(index); // Pointer to current student

        // Prompt player for input
        std::cout << "Student " << player->getColour() << ", where do you want to complete an Assignment?" << std::endl;
        std::cout << "> ";

        // Handle invalid intersections
        while(std::cin >> intersection && !board->isValid(intersection)) {
            std::cout << "You cannot build here." << std::endl;
            std::cout << "> ";
        }
        
        // Complete specified criterion under current player
        board->sortedCriteria[intersection]->complete(player);
    }

    // Display updated board
    board->display();
}
