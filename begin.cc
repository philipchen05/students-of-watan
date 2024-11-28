#include "begin.h"
#include "gamephase.h"
#include "game.h"
#include "board.h"

#include <iostream>
#include <string>

// Begin constructor
Begin::Begin(Game* game) : GamePhase{game} {}

// Method for executing beginning of game events
void Begin::play() {
    const int numTurns = game->getNumPlayers() * 2; // Total number of turns in beginning of game
    Board* board = game->getBoard(); // Pointer to Board

    // Prompt students for starting assignment location; first in order, then in reverse-order
    for(int i = 0; i < numTurns; i++) {
        int index = i > 3 ? numTurns - 1 - i : i; // Calculate index number of player whose turn it is to choose an assignment
        int intersection; // Stores player input for desired intersection
        Student* player = game->getPlayer(index); // Pointer to current student

        // Prompt player for input
        std::cout << "Student " << player->getColour() << ", where do you want to complete an Assignment?" << std::endl;
        std::cout << "> ";

        // Handle invalid intersections
        while(std::cin >> intersection && !board->canBuildCriteria(intersection, *player, true)) {
            std::cout << "You cannot build here." << std::endl;
            std::cout << "> ";
        }
        
        // Complete specified criterion under current player
        std::cerr << "Begin::play() - completing " << *board->getCriterion(intersection) << std:: endl;
        Criterion* criterion = board->getCriterion(intersection);
        criterion->complete(player);
        player->addCriterion(criterion);
    }

    // Display updated board
    board->display();
}
