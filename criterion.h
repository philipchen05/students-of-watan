#ifndef CRITERION_H
#define CRITERION_H

#include "achievement.h"
#include "resource.h"


#include <string>

class Criterion: public Achievement {
  public:
    enum class CompletionLevel {INCOMPLETE = 0, ASSIGNMENT, MIDTERM, EXAM}; // completion levels

    // maps current level to the cost of upgrading to the next level,
    // where a cost is a map from each resource to the amount needed
    static const std::map<CompletionLevel, std::map<Resource, int>> upgradeCosts;

  private:
    CompletionLevel completion; // current level of completion
    std::map<CompletionLevel, std::map<Resource, int>> upgradeCost; // maps current level to the cost of upgrading to the next level,
    // where cost is a map from each resource to the amount of that resource needed

  public:
    Criterion(int id, std::shared_ptr<Student> owner = nullptr, CompletionLevel completion = CompletionLevel::INCOMPLETE); // ctor

    void complete(std::shared_ptr<Student> s); // makes criterion completed by the given student (which becomes criterion's owner)
    void improve(); // attempts to upgrade to the next level (midterm or exam)

    void notify(const Subject *sbj) override; // adds the earned resources to owner

    int getCompletion() const; // returns the completion level (incomplete, assignment, midterm, exam)
    const std::map<Resource, int>& getUpgradeCost() const override; // returns the cost of upgrading to next level

    ~Criterion() override;
};

#endif
