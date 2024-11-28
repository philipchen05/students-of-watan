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
        
        Resource tileType = resourceFromInt(type);
        // Create the tile
        auto tile = std::make_unique<Tile>(tileType, value, i, TileCriteria, TileGoals);

        // Add the tile to the tiles vector
        tiles.push_back(std::move(tile));
    }

    return tiles; // Return the constructed vector of tiles
}

FileSetup::FileSetup(const std::string& boardDataString) : boardDataString{boardDataString} {}

std::vector<std::unique_ptr<Tile>> FileSetup::generateTiles(
    const std::vector<std::shared_ptr<Criterion>>& criteria,
    const std::vector<std::shared_ptr<Goal>>& goals) {

    ////////////////
    std::istringstream iss(boardDataString);
    std::vector<int> boardData;
    int num;

    // Read all integers from the line
    while (iss >> num) {
        boardData.push_back(num);
    }

    std::vector<std::unique_ptr<Tile>> tiles;

    for (int i = 0; i < 19; ++i) {
        int type = boardData[i * 2];
        // Special handling for NETFLIX (type == 5)
        int value = (type == 5) ? 0 : boardData[i * 2 + 1];

        // Create the tile
        std::vector<std::shared_ptr<Criterion>> TileCriteria;
        std::vector<std::shared_ptr<Goal>> TileGoals;

        for (int j = 0; j < 6; j++) {
            TileCriteria.push_back(criteria[tilesCriteria[i][j]]);
            TileGoals.push_back(goals[tilesGoals[i][j]]);
        }
        Resource tileType = resourceFromInt(type);

        // Create the tile
        auto tile = std::make_unique<Tile>(tileType, value, i, TileCriteria, TileGoals);

        // Add the tile to the tiles vector
        tiles.push_back(std::move(tile));
    }

    return tiles;
}