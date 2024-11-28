#include "loadedroll.h"
#include <iostream>
#include <string>

// Roll method
int LoadedRoll::roll() {
    int input; // Student input

    std::cout << "Input a roll between 2 and 12:" << std::endl; // Prompt student for roll value
    std::cout << "> ";

    // Loop to handle invalid input
    while(!(std::cin >> input) || input < 2 || input > 12) {
        std::cin.clear(); // Clear previous invalid input from input stream
        std::cout << "Invalid roll." << std::endl;
        std::cout << "Input a roll between 2 and 12:" << std::endl; // Prompt student for roll value again
        std::cout << "> ";
    }

    return input; // Return student input
}
