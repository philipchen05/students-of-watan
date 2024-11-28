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
    bool owned; // true if achievement has an owner, otherwise false
    Student* owner; // student that has completed/achieved this achievement

    Achievement(int id, Student* owner = nullptr); // constructor

  public:
    virtual void notify(const Subject *sbj); // called by subject

    bool isOwned() const; // returns true if achievement has owner, otherwise false
    std::string getOwnerName() const; // returns owner's colour if achievement has owner, otherwise empty string
    int getId() const; // returns achievement's id (number)

    // returns cost of upgrading (or acquiring) an achievement
    virtual const std::map<Resource, int>& getUpgradeCost() const = 0;

    virtual ~Achievement() = 0; // abstract class
};

#endif
