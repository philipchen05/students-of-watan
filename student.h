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
    static const std::map<Resource, int> defaultResources;

    std::string colour; // student's colour (name)
    int number; // student's place in order of turns [1, 4]
    std::map<Resource, int> resources; // number of each resource that student has: resource |-> amount

    std::vector<std::shared_ptr<Criterion>> criteria; // list of all criteria that student has completed
    std::vector<std::shared_ptr<Goal>> goals; // list of all goals that student has achieved

  public:
    Student(std::string colour, int number, int numVP = 0, const std::map<Resource, int> &resources = defaultResources, 
            std::vector<std::shared_ptr<Criterion>> criteria = {}, std::vector<std::shared_ptr<Goal>> goals = {});

    void addCriterion(Criterion *c); // adds criterion to student's list of completed criteria
    void improve(Criterion *c); // attempts to improve the given criterion
    void addGoal(Goal *g); // adds goal to the list of student's list of achieved goals

    void addResources(Resource type, int amount); // adds specified amount of the specified resource
    void removeResources(Resource type, int amount); // removes specified amount of the specified resource

    const std::string& getColour() const; // returns student colour (name)
    int getVP() const; // returns number of victory points
    const std::map<Resource, int>& getResources() const; // returns student's current resources
    int getResource(Resource type) const; // returns the number of resources of the given type
    int getTotalResources() const; // returns total number of resources
    std::string getData() const; // returns string with all student data to be saved to file
    
    void printStatus() const; // prints status (victory points and available resources)
    void printCriteria() const; // prints completed criteria

    ~Student();
};

#endif
