#include "game.h"
#include "student.h"
#include "gamePhase.h"

// Game constructor
Game::Game() : board{std::make_unique<Board>()}, players{std::vector<unique_ptr<Student>>(4)}, gamePhase{nullptr} {
    std::vector<string> colours = {"Blue", "Red", "Orange", "Yellow"};

    // Initialize Students
    for(size_t i = 0; i < players.size(); i++) {
        players[i] = std::make_unique<Student>(colours[i]);
    }
}

// Method for playing game
void Game::play() {
    do {
        // Play beginning of game
        gamePhase = std::make_unique<Begin>();
        gamePhase->play();

        while(!hasWon()) {
            // Turns
        }

        // Play end of game
        gamePhase = std::make_unique<End>();
        gamePhase->play();        
    } while(gamePhase->playAgain());
}

// Helper method for determining if a player has won
boolean Game::hasWon() {
    // Iterate through players
    for(const auto& s : players) {
        if(s->numVP >= 10) {
            return true; // Return true if a player has at least 10 victory points (that player has won)
        }
    }
    return false; // Otherwise, return false if no player has at least 10 victory points
}
