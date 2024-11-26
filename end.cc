#include "end.h"
#include <iostream>

// End constructor
End::End() : response{""} {}

// Method for executing end of game events
void End::play() {
    string res; // Stores response from player(s)

    // Prompt player(s) for input
    std::cout << "Would you like to play again?" << std::endl;
    std::cout << "> ";
    std::cin >> res;

    // Interpret response
    if(res == "yes") {
        playAgain = true;
    } else {
        playAgain = false;
    }
}

// Returns true if players wish to play again
boolean End::playAgain() const {
    return playAgain;
}
