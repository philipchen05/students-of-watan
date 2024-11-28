#ifndef BOARDSETUP_H
#define BOARDSETUP_H

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "tile.h"
#include <map>
#include <set>

class BoardSetup {
    protected:
        // a map of each tile's criteria (vertices)
        std::map<int, std::vector<int>> tilesCriteria = {{0, {0, 1, 3, 4, 8, 9}}, {1, {2, 3, 7, 8, 13, 14}}, {2, {4, 5, 9, 10, 15, 16}},
                                                      {3, {6, 7, 12, 13, 18, 19}}, {4, {8, 9, 14, 15, 20, 21}}, {5, {10, 11, 16, 17, 22, 23}},
                                                      {6, {13, 14, 19, 20, 25, 26}}, {7, {15, 16, 21, 22, 27, 28}}, {8, {18, 19, 24, 25, 30, 31}},
                                                      {9, {20, 21, 26, 27, 32, 33}}, {10, {22, 23, 28, 29, 34, 35}}, {11, {25, 26, 31, 32, 37, 38}},
                                                      {12, {27, 28, 33, 34, 39, 40}}, {13, {30, 31, 36, 37, 42, 42}}, {14, {32, 33, 38, 39, 44, 45}},
                                                      {15, {34, 35, 40, 41, 46, 47}}, {16, {37, 38, 43, 44, 48, 49}}, {17, {39, 40, 45, 46, 50, 51}},
                                                      {18, {44, 45, 49, 50, 52, 53}}
                                                      };
        // a map of each tile's goals (edges)
        std::map<int, std::vector<int>> tilesGoals = { {0, {0, 1, 2, 6, 7, 10}}, {1, {3, 5, 6, 13, 14, 18}}, {2, {4, 7, 8, 15, 16, 19}},
                                                    {3, {9, 12, 13, 20, 21, 26}}, {4, {10, 14, 15, 22, 23, 27}}, {5, {11, 16, 17, 24, 25, 28}},
                                                    {6, {18, 21, 22, 30, 31, 35}}, {7, {19, 23, 24, 32, 33, 36}}, {8, {26, 29, 30, 37, 38, 43}},
                                                    {9, {27, 31, 32, 39, 40, 44}}, {10, {28, 33, 34, 41, 42, 45}}, {11, {35, 38, 39, 47, 48, 52}},
                                                    {12, {36, 40, 41, 49, 50, 53}}, {13, {43, 46, 47, 54, 55, 60}}, {14, {44, 48, 49, 56, 57, 61}},
                                                    {15, {45, 50, 51, 58, 59, 62}}, {16, {52, 55, 56, 63, 64, 67}}, {17, {53, 57, 58, 65, 66, 68}},
                                                    {18, {61, 64, 65, 69, 70, 71}}
                                                    };

    public:

        virtual std::vector<std::unique_ptr<Tile>> generateTiles(
        const std::vector<std::shared_ptr<Criterion>>& criteria,
        const std::vector<std::shared_ptr<Goal>>& goals) = 0;
        virtual ~BoardSetup() = default;
};

class FileSetup : public BoardSetup {
    private:
        std::string boardDataString;
    public:
        FileSetup(const std::string& boardDataString);
        std::vector<std::unique_ptr<Tile>> generateTiles(
                const std::vector<std::shared_ptr<Criterion>>& criteria,
                const std::vector<std::shared_ptr<Goal>>& goals) override;
};

class RandomSetup : public BoardSetup {
    private: 
        int seed;

    public:
        RandomSetup(int seed);
        std::vector<std::unique_ptr<Tile>> generateTiles(
                const std::vector<std::shared_ptr<Criterion>>& criteria,
                const std::vector<std::shared_ptr<Goal>>& goals
        ) override;
    };

#endif
