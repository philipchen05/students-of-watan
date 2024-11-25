#ifndef GOAL_H
#define GOAL_H

#include "achievement.h"

#include <string>

class Goal: public Achievement {
  private:
    bool achieved;
    
  public:
    ~Goal();
};

#endif
