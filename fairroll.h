#ifndef FAIRROLL_H
#define FAIRROLL_H

// FairRoll class for fair dice roll algorithm
class FairRoll: public DiceRoll {
    public:
        int roll() const override; // Roll method
};

#endif
