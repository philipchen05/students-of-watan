#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include "observer.h"
#include "student.h"
#include "resource.h"

#include <map>
#include <memory>

class Student; // forward declaration

class Achievement: public Observer {
  protected:
    int id; // identifying number
    std::shared_ptr<Student> owner; // student that has completed/achieved this achievement

    Achievement(int id, std::shared_ptr<Student> owner = nullptr); // constructor

  public:
    virtual void notify(const Subject *sbj); // called by subject

    std::string getOwnerName() const; // gets colour (name) of owner
    int getId() const; // gets achievement's id (number)

    // returns cost of upgrading (or acquiring) an achievement
    virtual const std::map<Resource, int>& getUpgradeCost() const = 0;

    virtual ~Achievement() = 0; // abstract class
};

#endif
