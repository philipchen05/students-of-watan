#ifndef TURNBEGIN_H
#define TURNBEGIN_H

#include "turn.h"
#include "dice.h"
#include "resource.h"

// TurnBegin class for managing beginning of player turn
class TurnBegin: public Turn {
    private:
        Dice dice; // Dice object
        std::mt19937& gen; // Random number generator
        void moveGeese(); // Move geese to new location
        void updateResources(int roll); // Update player resources based on dice roll
        bool printUpdates(std::vector<const std::map<Resource, int>*> &prevResources, bool gain, std::vector<int>* amountsLost) const; // Output resource updates; returns true if at least one resource updated
        bool printGains(std::vector<const std::map<Resource, int>*> &prevResources) const; // Output resource gains; returns true if at least one resource was gained
        bool printLosses(std::vector<const std::map<Resource, int>*> &prevResources, std::vector<int>* amountsLost) const; // Output resource losses; returns true if at least one resource was lost
        Resource loseResource(const Student& s); // Loses one random resource and returns it; proportional probabilities of losing each resource
    public:
        TurnBegin(Student* player, mt19937& gen); // TurnBegin constructor
        virtual ~TurnBegin() = default; // TurnBegin destructor
        void play() override; // Method for playing beginning of turn events
};

#endif
