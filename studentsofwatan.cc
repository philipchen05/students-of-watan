#include "game.h"

// Main method for executing program
int main(int argc, char* argv[]) {
    int seed = Game::getDefaultSeed(); // Game seed for random number generation
    std::string load = ""; // Load file
    std::string board = ""; // Board file

    // Parse flags (if any)
    for(int i = 0; i < argc; i++) {
        std::string arg = std::string(argv[i]);
        if(arg == "-seed") {
            seed = stoi(std::string(argv[i + 1]));
            i++;
        } else if(arg == "-load") {
            load = argv[i + 1];
            i++;
        } else if(arg == "-board") {
            board = argv[i + 1];
            i++;
        }
    }

    Game game{seed, load, board}; // Construct game
    game.play(); // Play game
}