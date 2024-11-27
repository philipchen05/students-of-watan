#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "turnend.h"
#include <vector>
#include <memory>

// Game class; controls game flow
class Game {
    private:
        std::unique_ptr<Board> board; // Unique pointer to Board object 
        std::vector<std::unique_ptr<Student>> players; // Vector containing pointers to players
        std::unique_ptr<GamePhase> gamePhase; // Unique pointer to GamePhase object

        bool hasWon() const; // Helper method for determining if a player has won
    public:
        Game(); // Game constructor

        int getNumPlayers() const; // returns number of players
        Student* getPlayer(int index) const; // returns raw pointer to the index-th player
        Board* getBoard() const; // returns raw pointer to board 

        void play(); // Method for playing game
};

#endif
