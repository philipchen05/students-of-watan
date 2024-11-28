#ifndef CRITERION_H
#define CRITERION_H

#include "achievement.h"
#include "resource.h"

#include <string>
#include <ostream>

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
    Criterion(int id, Student* owner = nullptr, CompletionLevel completion = CompletionLevel::INCOMPLETE); // ctor

    void complete(Student* s); // sets criterion as completed by the given student
    void improve(); // upgrades criterion to the next completion level (e.g. assignment to midterm)

    void notify(const Subject *sbj) override; // adds resources earend from the notifying tile to the owner

    int getCompletion() const; // returns an integer [0, 3] representing the completion level 
    const std::map<Resource, int>& getUpgradeCost() const override; // returns the cost of upgrading to next level

    ~Criterion() override;
};

// prints criterion contents for debug [Criterion: (id: ID, owner: OWNER, comp: COMPLETIONLEVEL)]
std::ostream& operator<<(std::ostream &out, const Criterion &criterion);

#endif
