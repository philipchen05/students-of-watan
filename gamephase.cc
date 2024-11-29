#include "gamephase.h"
#include "student.h"
#include "game.h"

#include <fstream>

// GamePhase constructor
GamePhase::GamePhase(Game* game) : game{game} {}

bool GamePhase::getPlayAgain() const {
    return false;
}

// Saves current game state to specified file
void GamePhase::save(std::string file, Student* player) {
    std::ofstream out{file}; // Output file stream

    // save current player's turn
    out << player->getColour() << std::endl;

    // save all player data
    for(int i = 0; i < game->getNumPlayers(); i++) {
        Student* s = game->getPlayer(i); // Pointer to current player
        out << s->getData() << std::endl;
    }

    // save board data
    out << game->getBoard()->getData() << std::endl;

    // save geese location
    if (game->getBoard()->getGeeseLocation() != nullptr) {
        out << game->getBoard()->getGeeseLocation()->getLocation() << std::endl;
    } else {
        out << "-1" << std::endl;
    }
    out.close();
}