#include "tile.h"

#include <memory>

Tile::Tile(Resource type, int value, int location, const std::vector<std::shared_ptr<Criterion>> &criteria, std::vector<std::shared_ptr<Goal>> goals):
    Subject{},
    type{type},
    value{value},
    location{location},
    criteria{criteria},
    goals{goals} {}

// returns true if there are geese on the tile, otherwise false
bool Tile::hasGeese() const {
    return geese;
}

// returns type of resource
Resource Tile::getType() const { 
    return type;
}

// returns value of tile
int Tile::getValue() const {
    return value;
}

// sets whether or not geese are on tile
void Tile::setGeese(bool geese) {
    this->geese = geese;
}
