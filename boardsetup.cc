#include <random>   
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include "boardsetup.h"
#include "tile.h" 
#include "resource.h"


RandomSetup::RandomSetup(std::mt19937 &gen) : gen{gen} {}

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
        2,                           // One 2
        12,                          // One 12
        3, 3, 4, 4, 5, 5, 6, 6,      // Two each of 3-6
        8, 8, 9, 9, 10, 10, 11, 11   // Two each of 8-11
    };

    // Create the tiles
    std::vector<std::unique_ptr<Tile>> tiles;

    for (int i = 0; i < 19; ++i) {
        std::vector<std::shared_ptr<Criterion>> TileCriteria;
        std::vector<std::shared_ptr<Goal>> TileGoals;
        std::uniform_int_distribution<> resourceDistrib{0, static_cast<int>(resources.size() - 1)}; // Range between 0 and resources.size() - 1 (inclusive)
        std::uniform_int_distribution<> valueDistrib{0, static_cast<int>(values.size() - 1)}; // Range between 0 and values.size() - 1 (inclusive)

        int resourceIndex = resourceDistrib(gen);
        int type = resources[resourceIndex];
       
        // Assign value based on the resource
        int value = 0; // Default value for Netflix (resource 5)
        if (type != 5) {
            // Randomly pick a value for non-Netflix resources
            int valueIndex = valueDistrib(gen);
            value = values[valueIndex];
            // Remove the selected value from the values vector
            values.erase(values.begin() + valueIndex);
        }
        // Remove the selected resource from the vector
        resources.erase(resources.begin() + resourceIndex);
         
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