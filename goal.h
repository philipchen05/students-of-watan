#ifndef GOAL_H
#define GOAL_H

#include "achievement.h"
#include "resource.h"
#include "student.h"

#include <string>

class Student; // forward declaration
class Criterion; // forward declaration
class Achievement; // forward declaration

class Goal: public Achievement {
  private:
    bool achieved;
    std::map<Resource, int> upgradeCost;
    
  public:
    Goal(int id, std::shared_ptr<Student> owner = nullptr, bool achieved = false); // ctor
    const std::map<Resource, int>& getUpgradeCost() const override; // returns the cost of upgrading to the next level (i.e. acheiving the goal)
    ~Goal();
};

#endif
