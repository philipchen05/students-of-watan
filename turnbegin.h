#ifndef TURNBEGIN_H
#define TURNBEGIN_H

#include "turn.h"
#include "dice.h"

// TurnBegin class for managing beginning of player turn
class TurnBegin: public Turn {
    private:
        Dice dice; // Dice object
    public:
        TurnBegin(Student* player); // TurnBegin constructor
        virtual ~TurnBegin() = default; // TurnBegin destructor
        void play() override; // Method for playing beginning of turn events
};

#endif
