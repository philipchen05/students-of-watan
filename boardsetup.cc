#include <algorithm> // For std::shuffle
#include <random>    // For random number generation
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include "boardsetup.h"
#include "tile.h" // Include your Tile class header file
#include "resource.h"

RandomSetup::RandomSetup(int seed) : seed{seed} {}

std::vector<std::unique_ptr<Tile>> RandomSetup::generateTiles(
    const std::vector<std::shared_ptr<Criterion>>& criteria,
    const std::vector<std::shared_ptr<Goal>>& goals
) {
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
    std::vector<std::shared_ptr<Criterion>> TileCriteria;
    std::vector<std::shared_ptr<Goal>> TileGoals;

    for (int i = 0; i < 19; ++i) {
        int type = resources[i];
        int value = values[i]; 
        for (int j = 0; j < 6; j++) {
            TileCriteria.push_back(criteria[tilesCriteria[i][j]]);
            TileGoals.push_back(goals[tilesGoals[i][j]]);
        }
        
        Resource tileType;
        switch (type) {
            case (0): tileType = Resource::CAFFEINE;break;
            case (1): tileType =Resource::LAB;break;
            case (2): tileType =Resource::LECTURE;break;
            case (3): tileType =Resource::STUDY;break;
            case (4): tileType =Resource::TUTORIAL;break;
            default: tileType =Resource::NETFLIX;break;
        }
        // Create the tile
        auto tile = std::make_unique<Tile>(tileType, value, i, TileCriteria, TileGoals);// EDIT THIS LATER TO ADD CRITERIA AND GOALS

        // Add the tile to the tiles vector
        tiles.push_back(std::move(tile));
    }

    return tiles; // Return the constructed vector of tiles
}

FileSetup::FileSetup(const std::string& filename) : filename{filename} {}

std::vector<std::unique_ptr<Tile>> FileSetup::generateTiles(
    const std::vector<std::shared_ptr<Criterion>>& criteria,
    const std::vector<std::shared_ptr<Goal>>& goals) {
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
        std::vector<std::shared_ptr<Criterion>> TileCriteria;
        std::vector<std::shared_ptr<Goal>> TileGoals;

        for (int j = 0; j < 6; j++) {
            TileCriteria.push_back(criteria[tilesCriteria[i][j]]);
            TileGoals.push_back(goals[tilesGoals[i][j]]);
        }
        Resource tileType;
        switch (type) {
            case (0): tileType = Resource::CAFFEINE;break;
            case (1): tileType =Resource::LAB;break;
            case (2): tileType =Resource::LECTURE;break;
            case (3): tileType =Resource::STUDY;break;
            case (4): tileType =Resource::TUTORIAL;break;
            default: tileType =Resource::NETFLIX;break;
        }
        // Create the tile
        auto tile = std::make_unique<Tile>(tileType, value, i, TileCriteria, TileGoals);// EDIT THIS LATER TO ADD CRITERIA AND GOALS

        // Add the tile to the tiles vector
        tiles.push_back(std::move(tile));
    }

    return tiles;
}