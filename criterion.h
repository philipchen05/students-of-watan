#ifndef CRITERION_H
#define CRITERION_H

#include "achievement.h"

#include <string>

class Criterion: public Achievement {
  public:
    enum class CompletionLevel {ASSIGNMENT = 1, MIDTERM, EXAM};

    void update();

    CompletionLevel getCompletion(); // getter

    ~Criterion();

  private:
    CompletionLevel completion;
};

#endif
