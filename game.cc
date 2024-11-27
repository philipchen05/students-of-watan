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
    int turn = 0; // Stores turn number; used for determining which player's turn it is

    do {
        // Play beginning of game
        gamePhase = std::make_unique<Begin>(this);
        gamePhase->play();

        // Continue taking turns while nobody has won
        while(!hasWon()) {
            // Beginning of turn
            gamePhase = std::make_unique<TurnBegin>(this, players[turn % players.size()]);
            gamePhase->play();

            // End of turn
            gamePhase = std::make_unique<TurnEnd>(this, players[turn % players.size()]);
            gamePhase->play();

            turn++; // Increment turn number
        }

        // Play end of game
        gamePhase = std::make_unique<End>(this);
        gamePhase->play();        
    } while(gamePhase->playAgain());
}

// Helper method for determining if a player has won
boolean Game::hasWon() const {
    const int winVP = 10; // 10 victory points needed to win

    // Iterate through players
    for(const auto& s : players) {
        if(s->numVP >= winVP) {
            return true; // Return true if a player has at least the number of victory points needed to win
        }
    }
    return false; // Otherwise, return false if no player has won
}
