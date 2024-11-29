#ifndef TURN_H
#define TURN_H

#include "gamephase.h"
#include "student.h"

// Turn abstract class
class Turn: public GamePhase {
    protected:
        Student* player; // Pointer to player whose turn it is
        std::string toUpper(const std::string& str); // Converts string to uppercase
        std::string formatName(const std::string& str); // Converts player name to specified capitalization format (Blue, Red, etc.)
    public:
        Turn(Game* game, Student* player); // Turn constructor
        Student* getPlayer(); // returns raw ptr to player
        virtual ~Turn() = default; // Turn destructor
};

#endif
