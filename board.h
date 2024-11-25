#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <memory>
#include "tile.h"
#include "boardsetup.h"

class Board {
private:
    std::vector<std::shared_ptr<Tile>> tiles;

public:
    Board(std::unique_ptr<BoardSetup> setup);
    void display() const;
};

#endif