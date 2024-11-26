#ifndef BOARDSETUP_H
#define BOARDSETUP_H

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "tile.h"

class BoardSetup {
public:
    virtual std::vector<std::unique_ptr<Tile>> generateTiles() = 0;
    virtual ~BoardSetup() = default;
};

class FileSetup : public BoardSetup {
    private:
        std::string filename;
    public:
        FileSetup(const std::string& filename);
        std::vector<std::unique_ptr<Tile>> generateTiles() override;
};

class RandomSetup : public BoardSetup {
private: 
    int seed;

public:
    RandomSetup(int seed = 5555);
    std::vector<std::unique_ptr<Tile>> generateTiles() override;
};

#endif
