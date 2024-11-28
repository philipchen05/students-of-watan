#include "game.h"
#include "boardsetup.h"
#include "student.h"
#include "begin.h"
#include "turnbegin.h"
#include "end.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Game constructor
Game::Game(int seed, std::string load, std::string board) : board{nullptr}, players{std::vector<std::unique_ptr<Student>>(numPlayers)}, gamePhase{nullptr}, gen{seed}, seed{seed}, turn{0}, loaded{false} {
    if(load == "") { // Case: not loading game from file
        if(board == "") {
            board = std::make_unique<Board>(new RandomSetup{seed}); // Case: generate board from scratch
        } else {
            board = std::make_unique<Board>(new FileSetup{board}); // Case: load saved board
        }
        // Initialize new Students in index order
        initializePlayers();
    } else { // Case: loading previously saved game
        ifstream in{load}; // Input file stream to read in saved game file
        string curTurn; // Store current player turn by name (colour)
        std::vector<std::string> studentData(numPlayers); // Student data
        std::string boardData; // Board data
        int geese; // Geese location

        in >> curTurn;

        // Map player colour to index number and update turn field
        for(size_t i = 0; i < numPlayers; i++) {
            if(players[i]->getColour == curTurn) {
                turn = i;
            }
        }

        // Read in Student data
        for(int i = 0; i < numPlayers; i++) {
            std::string data;
            std::getline(in, data);
            studentData[i] = data;
        }

        // Set up board
        std::getline(in, boardData);
        board = std::make_unique<Board>(new FileSetup{boardData});

        // Set up students
        for(int i = 0; i < numPlayers; i++) {
            istringstream iss{playerData[i]}; // Input string stream from current player data
            players[i] = std::make_unique<Student>(colours[i]); // Initialize player
            Student* player& = players[i]; // Pointer to current player

            // Add resources
            for(Resource r : resources) {
                int amount;
                iss >> amount;
                player->addResources(r, amount);
            }

            // Add goals
            std::string s;
            iss >> s; // Throwaway 'g'
            iss >> s;
            while(s != "c") {
                int id = std::stoi(s); // Goal location
                Goal* goal = board->getGoals()[id]; // Pointer to goal
                goal->achieve(player);
                player->addGoal(goal);
            }

            // Add criteria
            while(iss >> s) {
                int id = std::stoi(s); // Criterion location
                Criterion* criterion = board->getCriteria()[id] // Pointer to criterion
                int completionLevel; // Criterion completion level
                iss >> completionLevel;
                criterion->complete(player);
                player->addCriterion(criterion);

                // Improve criterion if applicable
                for(int i = 0; i < completionLevel - 1; i++) {
                    criterion->improve();
                }
            }
        }

        // Set geese location
        in >> geese;
        board->tiles[geese]->setGeese(true);

        loaded = true;
    }
}

// Method for playing game
void Game::play() {
    do {
        if(!loaded) {
            // Play beginning of game
            gamePhase = std::make_unique<Begin>(this);
            gamePhase->play();
        }

        // Continue taking turns while nobody has won
        while(!hasWon()) {
            if()
            // Beginning of turn
            gamePhase = std::make_unique<TurnBegin>(this, players[turn % numPlayers]);
            gamePhase->play();

            // End of turn
            gamePhase = std::make_unique<TurnEnd>(this, players[turn % numPlayers]);
            gamePhase->play();

            turn++; // Increment turn number
        }

        // Play end of game
        gamePhase = std::make_unique<End>(this);
        gamePhase->play();

        // Reset game if players wish to play again
        if(gamePhase->playAgain()) {
            board = std::make_unique<Board>(new RandomSetup{seed}); // Reset Board (including goals and criteria)
            initializePlayer(); // Reset players
            loaded = false;
        }
    } while(gamePhase->playAgain());
}


// returns number of players
int Game::getNumPlayers() const {
    return players.size();
}

// returns pointer to board
Board* Game::getBoard() {
    return board.get();
}

// returns raw pointer to index-th player
Student* Game::getPlayer(int index) {
    return players.at(index).get();
}

// Initialize players at beginning of game
void Game::initializePlayers() {
    // Initialize Students in index order
    for(size_t i = 0; i < numPlayers; i++) {
        players[i] = std::make_unique<Student>(colours[i]);
    }

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
