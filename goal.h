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
  public:
    // cost of achieving this goal
    static const std::map<Resource, int> upgradeCost;
  private:
    bool achieved; // whether or not this goal was achieved 
    
  public:
    Goal(int id, std::shared_ptr<Student> owner = nullptr, bool achieved = false); // ctor
    void achieve(std::shared_ptr<Student> s); // sets goal as achieved by the given student
    const std::map<Resource, int>& getUpgradeCost() const override; // returns the cost of upgrading to the next level (i.e. achieving the goal)
    ~Goal();
};

#endif
