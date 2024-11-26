#ifndef BEGIN_H
#define BEGIN_H

#include <gamephase.h>
#include <memory>

// Begin class for managing beginning of game
class Begin: public GamePhase {
    public:
        Begin(Game* game); // Begin constructor
        ~Begin() = default; // Begin destructor
        void play() const override; // Method for executing beginning of game events
};

#endif
