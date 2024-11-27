#ifndef TILE_H
#define TILE_H

#include "subject.h"

#include <string>
#include <vector>
#include <memory>

#include "criterion.h"
#include "goal.h"
#include "resource.h"

class Tile: public Subject {
  private:
    Resource type;
    int value, location;
    bool geese;

    std::vector<std::shared_ptr<Criterion>> criteria;
    std::vector<std::shared_ptr<Goal>> goals;

  public:
    Tile(Resource type, int value, int location, const std::vector<std::shared_ptr<Criterion>> &criteria, const std::vector<std::shared_ptr<Goal>> &goals);

    bool hasGeese() const; // returns true if there are geese on the tile, otherwise false
    Resource getType() const; // returns type of resource
    int getValue() const; // returns value of tile

    void setGeese(bool geese); // sets whether or not geese are on tile
 
    ~Tile();
};

#endif
