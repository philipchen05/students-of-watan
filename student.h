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

    bool canAcquire(Achievement *a);

  public:
    Student(std::string colour, int number, int numVP = 0, const std::map<Resource, int> &resources = {});

    void complete(Criterion *c); // attempts to complete the given criterion

    void addResources(Resource type, int amount); // adds resources earned from the criterion

    std::string getColour() const; // gets student colour (name)
    void printStatus() const; // prints status (victory points and available resources)
    void printCriteria() const; // prints completed criteria

    ~Student();
};

#endif
