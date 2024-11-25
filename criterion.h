#ifndef CRITERION_H
#define CRITERION_H

#include "achievement.h"

#include <string>

class Criterion: public Achievement {
  public:
    enum class CompletionLevel {INCOMPLETE = 0, ASSIGNMENT, MIDTERM, EXAM};

  private:
    CompletionLevel completion;

  public:
    Criterion(int id, std::map<Resource, int> cost, std::shared_ptr<Student> owner = nullptr, CompletionLevel completion = CompletionLevel::INCOMPLETE);

    void update();

    CompletionLevel getCompletion() const; // getter

    ~Criterion() override;

};

#endif
