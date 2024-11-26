#include <algorithm> // For std::shuffle
#include <random>    // For random number generation
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include "boardsetup.h"
#include "tile.h" // Include your Tile class header file

RandomSetup::RandomSetup(int seed = 5555) : seed{seed} {}

std::vector<std::unique_ptr<Tile>> RandomSetup::generateTiles() {
    // Predefine the resources (types) according to constraints
    std::vector<int> resources = {
        0, 0, 0, 0,    // 4 CAFFEINE
        1, 1, 1, 1,    // 4 LAB
        2, 2, 2, 2,    // 4 LECTURE
        3, 3, 3,       // 3 STUDY
        4, 4, 4,       // 3 TUTORIAL
        5              // 1 NETFLIX
    };

    // Predefine the values according to constraints
    std::vector<int> values = {
        0,                           // One 0
        2,                           // One 2
        12,                          // One 12
        3, 3, 4, 4, 5, 5, 6, 6,      // Two each of 3-6
        8, 8, 9, 9, 10, 10, 11, 11   // Two each of 8-11
    };

    // Initialize random engine with the given seed
    std::default_random_engine rng(seed);

    // Shuffle resources and values using the seeded random engine
    std::shuffle(resources.begin(), resources.end(), rng);
    std::shuffle(values.begin(), values.end(), rng);

    // Create the tiles
    std::vector<std::unique_ptr<Tile>> tiles;

    for (int i = 0; i < 19; ++i) {
        int type = resources[i];
        int value = values[i]; 

        // Create the tile
        auto tile = std::make_unique<Tile>(i, value, type);// EDIT THIS LATER TO ADD CRITERIA AND GOALS

        // Add the tile to the tiles vector
        tiles.push_back(std::move(tile));
    }

    return tiles; // Return the constructed vector of tiles
}

FileSetup::FileSetup(const std::string& filename) : filename{filename} {}

std::vector<std::unique_ptr<Tile>> FileSetup::generateTiles() {
    std::ifstream file{filename};

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    // Read the entire line
    std::string line;
    if (!std::getline(file, line)) {
        throw std::runtime_error("File is empty or invalid format: " + filename);
    }

    std::istringstream iss(line);
    std::vector<int> boardData;
    int num;

    // Read all integers from the line
    while (iss >> num) {
        boardData.push_back(num);
    }

    // Ensure the data contains pairs of (type, value)
    if (boardData.size() != 38) { // 19 tiles * 2 (type + value)
        throw std::runtime_error("Invalid board data in file: " + filename);
    }

    std::vector<std::unique_ptr<Tile>> tiles;

    for (int i = 0; i < 19; ++i) {
        int type = boardData[i * 2];
        int value = boardData[i * 2 + 1];

        // Special handling for NETFLIX (type == 5)
        if (type == 5) {
            value = 0; // Indicate no value for NETFLIX
        }

        // Create the tile
        auto tile = std::make_unique<Tile>(i, value, type);

        // Add the tile to the tiles vector
        tiles.push_back(std::move(tile));
    }

    return tiles;
}