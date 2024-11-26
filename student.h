#ifndef STUDENT_H
#define STUDENT_H

#include "achievement.h"

#include <string>
#include <memory>
#include <map>

#include "criterion.h"
#include "goal.h"
#include "resource.h"

class Student {
  private:
    std::string colour;
    int number;

    std::map<Resource, int> resources;

    std::vector<std::shared_ptr<Criterion>> criteria;
    std::vector<std::shared_ptr<Goal>> goals;

  public:
    void complete(Criterion *c);
    std::string getColour() const;
    ~Student();
};

#endif
