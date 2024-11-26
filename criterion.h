#ifndef CRITERION_H
#define CRITERION_H

#include "achievement.h"
#include "resource.h"


#include <string>

class Criterion: public Achievement {
  public:
    enum class CompletionLevel {INCOMPLETE = 0, ASSIGNMENT, MIDTERM, EXAM};

  private:
    CompletionLevel completion;
    std::map<CompletionLevel, std::map<Resource, int>> upgradeCost;

  public:
    Criterion(int id, std::shared_ptr<Student> owner = nullptr, CompletionLevel completion = CompletionLevel::INCOMPLETE);

    void complete(std::shared_ptr<Student> s); // makes criterion completed by the given student (which becomes criterion's owner)
    void improve(); // attempts to upgrade to the next level (midterm or exam)

    void notify(const Subject *sbj) override; // adds the earned resources to owner

    int getCompletion() const; // returns the completion level (incomplete, assignment, midterm, exam)
    const std::map<Resource, int>& getUpgradeCost() const override; // returns the cost of upgrading to next level

    ~Criterion() override;
};

#endif
