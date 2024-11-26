#ifndef END_H
#define END_H

#include <memory>
#include <string>

// End class for managing end of game
class End: public GamePhase {
    private:
        string response;
    public:
        End(); // End constructor
        ~End() = default; // End destructor
        void play() override; // Method for executing end of game events
};

#endif
