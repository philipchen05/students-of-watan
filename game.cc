#include "game.h"
#include "boardsetup.h"
#include "student.h"
#include "begin.h"
#include "turnbegin.h"
#include "turnend.h"
#include "end.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

// Game constructor
Game::Game(int seed, std::string loadFile, std::string boardFile) : board{nullptr}, players{std::vector<std::unique_ptr<Student>>(numPlayers)}, gamePhase{nullptr}, seed{seed}, turn{0}, loaded{false}, gen{static_cast<uint32_t>(seed)} {
    // Initialize new Students in index order
    initializePlayers();
    if(loadFile == "") { // Case: not loading game from file
        if(boardFile == "") {
            board = std::make_unique<Board>(std::make_unique<RandomSetup>(gen)); // Case: generate board from scratch
        } else { // Case: load saved board
            std::ifstream in{boardFile}; // Input file stream to read in saved board file
            std::string boardData; // Board data
            
            std::getline(in, boardData); // Read line from file
            board = std::make_unique<Board>(std::make_unique<FileSetup>(boardData)); // Set up board using file setup
        }
    } else { // Case: loading previously saved game
        std::ifstream in{loadFile}; // Input file stream to read in saved game file
        std::string curTurn; // Store current player turn by name (colour)
        std::vector<std::string> studentData(numPlayers); // Student data
        std::string boardData; // Board data
        int geese; // Geese location


        getline(in, curTurn);

        // Map player colour to index number and update turn field
        for(size_t i = 0; i < numPlayers; i++) {
            if(players[i]->getColour() == curTurn) {
                turn = i;
            }
        }

        // Read in Student data
        for(size_t i = 0; i < numPlayers; i++) {
            std::string data;
            std::getline(in, data);
            studentData[i] = data;
        }

        // Set up board
        std::getline(in, boardData);

        // Prioritize board file for board setup if both board and load files present (overwrite boardData)
        if(boardFile != "") {
            std::ifstream boardInput{boardFile};
            std::getline(boardInput, boardData);
        }

        board = std::make_unique<Board>(std::make_unique<FileSetup>(boardData));

        // Set up students
        for(size_t i = 0; i < numPlayers; i++) {
            std::istringstream iss{studentData[i]}; // Input string stream from current player data
            players[i] = std::make_unique<Student>(colours[i], i); // Initialize player
            Student* player = players[i].get(); // Pointer to current player

            // Add resources
            for(Resource r : resources) {
                int amount;
                iss >> amount;
                player->addResources(r, amount);
            }

            // Add goals
            std::string s;
            iss >> s; // Throwaway 'g'
            while(iss >> s) {
                if (s == "c") break; // c marks beginning of criteria
                int id = std::stoi(s); // Goal location
                Goal* goal = (board->getGoals()[id]).get(); // Pointer to goal
                goal->achieve(player);
                player->addGoal(goal);
            }

            // Add criteria
            while(iss >> s) {
                int id = std::stoi(s); // Criterion location
                Criterion* criterion = (board->getCriteria()[id]).get(); // Pointer to criterion
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
        const int invalidGeeseLocation = -1; // "Location" of geese when geese are not present on board
        in >> geese;
        if(geese != invalidGeeseLocation) {
            board->getTiles()[geese].get()->setGeese(true);
        }

        loaded = true;
    }
}

// Method for playing game
void Game::play() {
    do {
        if(!loaded) {
            // Play beginning of game
            gamePhase = std::make_unique<Begin>(this);
            try {
                gamePhase->play();
            } catch(std::exception &e) {
                std::cout << std::endl << "Closing game..." << std::endl;
                throw std::invalid_argument{"QUIT"};
            }
        }

        // Continue taking turns while nobody has won
        while(!hasWon()) {
            // Beginning of turn
            if(!loaded) {
                gamePhase = std::make_unique<TurnBegin>(this, players[turn % numPlayers].get(), gen);
                try {
                    gamePhase->play();
                } catch (std::exception &e) {
                    std::cerr << "[Game::play() - TurnBegin] exception raised " << e.what() << std::endl;
                    std::cerr << "\tis EOF" << std::endl;
                    Turn* te = dynamic_cast<Turn*>(gamePhase.get());
                    gamePhase->save("backup.sv", te->getPlayer());
                    std::cout << std::endl << "Closing game..." << std::endl;
                    throw std::invalid_argument{"QUIT"};
                }
            }

            // End of turn
            gamePhase = std::make_unique<TurnEnd>(this, players[turn % numPlayers].get());
            try {
                gamePhase->play();
            } catch (std::exception &e) {
                std::cerr << "[Game::play() - TurnEnd] exception raised " << e.what() << std::endl;
                std::cerr << "\tis EOF" << std::endl;
                Turn* te = dynamic_cast<Turn*>(gamePhase.get());
                gamePhase->save("backup.sv", te->getPlayer());
                std::cout << std::endl << "Closing game..." << std::endl;
                throw std::invalid_argument{"QUIT"};
            }
            loaded = false;

            turn++; // Increment turn number
        }

        // Play end of game
        gamePhase = std::make_unique<End>(this);
        try {
            gamePhase->play();
        } catch (std::exception &e) {
            std::cout << std::endl << "Closing game..." << std::endl;
            throw std::invalid_argument{"QUIT"};
        }

        // Reset game if players wish to play again
        if(gamePhase->getPlayAgain()) {
            board = std::make_unique<Board>(std::make_unique<RandomSetup>(gen)); // Reset Board (including goals and criteria)
            initializePlayers(); // Reset players
            loaded = false;
            turn = 0;
        }
    } while(gamePhase->getPlayAgain());
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
        players[i] = std::make_unique<Student>(colours[i], i);
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
