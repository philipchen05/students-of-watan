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
    Tile(Resource type, int value, int location, std::vector<std::shared_ptr<Criterion>> criteria, std::vector<std::shared_ptr<Goal>> goals);

    bool geese();
    void setGeese(bool geese);

    ~Tile();
};

#endif
