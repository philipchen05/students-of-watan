#include "tile.h"

#include <memory>

Tile::Tile(Resource type, int value, int location, const std::vector<std::shared_ptr<Criterion>> &criteria, std::vector<std::shared_ptr<Goal>> goals):
    Subject{},
    type{type},
    value{value},
    location{location},
    criteria{criteria},
    goals{goals} {}

bool Tile::hasGeese() const {
    return geese;
}

Resource Tile::getType() const { 
    return type;
}

void Tile::setGeese(bool geese) {
    this->geese = geese;
}
