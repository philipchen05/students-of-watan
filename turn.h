#ifndef TURN_H
#define TURN_H

#include "gamephase.h"
#include "student.h"

// Turn abstract class
class Turn: public GamePhase {
    protected:
        Student* player; // Pointer to player whose turn it is
    public:
        Turn(Game* game, Student* player); // Turn constructor
        Student* getPlayer(); // returns raw ptr to player
        virtual ~Turn() = default; // Turn destructor
};

#endif
