#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "gamephase.h"
#include "resource.h"
#include "student.h"
#include <vector>
#include <memory>
#include <random>
#include <string>

// Game class; controls game flow
class Game {
    private:
        const std::vector<std::string> colours = {"Blue", "Red", "Orange", "Yellow"}; // Const vector storing player colours in specified game order
        const std::vector<Resource> resources = {Resource::CAFFEINE, Resource::LAB, Resource::LECTURE, Resource::STUDY, Resource::TUTORIAL}; // Const vector of resources in specified game order
        const size_t numPlayers = 4; // Number of players
        const size_t numResources = 5;
        static const int defaultSeed = 5489; // Default seed value

        std::unique_ptr<Board> board; // Unique pointer to Board object 
        std::vector<std::unique_ptr<Student>> players; // Vector containing pointers to players
        std::unique_ptr<GamePhase> gamePhase; // Unique pointer to GamePhase object
        int seed; // Seed for random number generation
        int turn; // Stores turn number; used for determining which player's turn it is
        bool loaded; // Whether or not game was loaded from previously saved game
        std::mt19937 gen; // Random number generator for game
        void initializePlayers(); // Initialize players at beginning of game
        bool hasWon() const; // Helper method for determining if a player has won
    public:
        Game(int seed, std::string loadFile, std::string boardFile); // Game constructor

        int getNumPlayers() const; // returns number of players
        Student* getPlayer(int index); // returns raw pointer to the index-th player
        Board* getBoard(); // returns raw pointer to board 

        void play(); // Method for playing game

        static const int getDefaultSeed() { return defaultSeed; }; // Returns default seed value
};

#endif
