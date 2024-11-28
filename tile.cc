#include "tile.h"

#include <memory>

Tile::Tile(Resource type, int value, int location, const std::vector<std::shared_ptr<Criterion>> &criteria, const std::vector<std::shared_ptr<Goal>>& goals):
    Subject{},
    type{type},
    value{value},
    location{location},
    criteria{criteria},
    goals{goals}
{
    std::cerr << *this << ": " << std::endl;
    std::cerr << "  criteria: " << std::endl;
    // attach all criteria (observers) to this tile (subject)
    for (auto cptr: criteria) {
        std::cerr << "\t" << *cptr << std::endl;
        this->attach(cptr.get());
    }

    std::cerr << "  goal: " << std::endl;
    for (auto gptr: goals) {
        std::cerr << "\t" << *gptr << std::endl;
    }
}

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

// returns location of tile
int Tile::getLocation() const {
    return location;
}

// return criteria associated with tile
std::vector<std::shared_ptr<Criterion>>& Tile::getCriteria() {
    return criteria;
}

// return goals associated with tile
std::vector<std::shared_ptr<Goal>>& Tile::getGoals() {
    return goals;
}

// sets whether or not geese are on tile
void Tile::setGeese(bool geese) {
    this->geese = geese;
}

Tile::~Tile() {}

// prints tile contents for debug [Tile: (type: TYPE, loc: LOCATION, val: VALUE)]
std::ostream& operator<<(std::ostream &out, const Tile &tile) {
    out << "[Tile: (type: " << resourceToString(tile.getType()) << ", loc: " << tile.getLocation() << ", val: " << tile.getValue() << ")]";
    return out;
}