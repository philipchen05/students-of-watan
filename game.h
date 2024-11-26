#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>



// Game class; controls game flow
class Game {
    private:
        std::unique_ptr<Board> board; // Unique pointer to Board object 
        std::vector<std::shared_ptr<Student>> players; // Vector containing pointers to players
        std::unique_ptr<GamePhase> gamePhase; // Unique pointer to GamePhase object

        boolean hasWon(); // Helper method for determining if a player has won
    public:
        Game(); // Game constructor
        void play(); // Method for playing game
};

#endif
