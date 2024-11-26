#ifndef STUDENT_H
#define STUDENT_H

#include "achievement.h"
#include "resource.h"

#include <string>
#include <memory>
#include <map>


// forward declaration
class Goal; 
class Criterion;
class Achievement;

class Student {
  private:
    std::string colour; // student's colour (name)
    int number; // student's place in order of turns [1, 4]
    int numVP; // number of victory points student has
    std::map<Resource, int> resources; // number of each resource that student has: resource |-> amount

    std::vector<std::shared_ptr<Criterion>> criteria; // list of all criteria that student has completed
    std::vector<std::shared_ptr<Goal>> goals; // list of all goals that student has achieved

  public:
    Student(std::string colour, int number, int numVP = 0, const std::map<Resource, int> &resources = {});

    void addCriterion(Criterion *c); // adds criterion to student's list of completed criteria
    void improve(Criterion *c); // attempts to improve the given criterion
    void addGoal(Goal *g); // adds goal to the list of student's list of achieved goals

    void addResources(Resource type, int amount); // adds specified amount of the specified resource
    void removeResources(Resource type, int amount); // removes specified amount of the specified resource
    void addVP(int amount); // adds the specified amount of victory points

    const std::string& getColour() const; // returns student colour (name)
    int getVP() const; // returns number of victory points
    const std::map<Resource, int>& getResources() const; // returns student's current resources
    
    void printStatus() const; // prints status (victory points and available resources)
    void printCriteria() const; // prints completed criteria

    ~Student();
};

#endif
