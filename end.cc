#include "end.h"
#include <iostream>
#include <stdexcept>

// End constructor
End::End(Game* game) : GamePhase{game}, playAgain{false} {}

// Method for executing end of game events
void End::play() {
    std::string res; // Stores response from player(s)

    // Prompt player(s) for input
    std::cout << "Would you like to play again?" << std::endl;
    std::cout << "> ";
    while (std::cin >> res) {
        if (res != "yes" && res != "no") {
            std::cout << "Invalid command." << std::endl;
            std::cout << "> ";
        } else {
            break;
        }
    }

    // Interpret response
    if (std::cin.eof()){
        throw std::invalid_argument{"EOF"};
    } else if(res == "yes") {
        playAgain = true;
    } else {
        playAgain = false;
    }
}

// Returns true if players wish to play again
bool End::getPlayAgain() const {
    return playAgain;
}
