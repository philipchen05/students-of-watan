#ifndef BOARDSETUP_H
#define BOARDSETUP_H

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "tile.h"

class BoardSetup {
public:
    virtual std::vector<std::shared_ptr<Tile>> generateTiles() = 0;
    virtual ~BoardSetup() = default;
};

class FileSetup : public BoardSetup {
    private:
        std::string file;
    public:
        FileSetup(const std::string& filename);
        std::vector<std::shared_ptr<Tile>> generateTiles() override;
};

class RandomSetup : public BoardSetup {
public:
    std::vector<std::shared_ptr<Tile>> generateTiles() override;
};

#endif
