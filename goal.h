#ifndef GOAL_H
#define GOAL_H

#include "achievement.h"

#include <string>

class Goal: public Achievement {
  private:
    bool achieved;
    
  public:
    Goal(int id, std::map<Resource, int> cost, std::shared_ptr<Student> owner = nullptr, bool achieved = false);
    ~Goal();
};

#endif
