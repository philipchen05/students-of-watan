#include "game.h"
#include "student.h"
#include "begin.h"
#include "turnbegin.h"
#include "end.h"

// Game constructor
Game::Game() : board{std::make_unique<Board>()}, players{std::vector<std::unique_ptr<Student>>(4)}, gamePhase{nullptr} {
    std::vector<std::string> colours = {"Blue", "Red", "Orange", "Yellow"};

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

// returns number of players
int Game::getNumPlayers() const {
    return players.size();
}
// returns pointer to board
Board* Game::getBoard() const {
    return board.get();
}
// returns raw pointer to index-th player
Student* Game::getPlayer(int index) const {
    return players.at(index).get();
}

// Helper method for determining if a player has won
bool Game::hasWon() const {
    const int winVP = 10; // 10 victory points needed to win

    // Iterate through players
    for(const auto& s : players) {
        if(s->getVP() >= winVP) {
            return true; // Return true if a player has at least the number of victory points needed to win
        }
    }
    return false; // Otherwise, return false if no player has won
}
