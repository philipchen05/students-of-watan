#include "turn.h"
#include "student.h"

Turn::Turn(Game* game, Student* player) : GamePhase{game}, player{player} {}

Student* Turn::getPlayer() {
    return player;
}

// Converts string to uppercase
std::string Turn::toUpper(const std::string& str) {
    std::string res = str;
    // Iterate over each character and convert to uppercase
    for (char& c : res) {
        c = std::toupper(static_cast<unsigned char>(c));
    }
    return res;
}

// Converts player name to specified capitalization format (Blue, Red, etc.)
std::string Turn::formatName(const std::string& str) {
    std::string res = str;
    // Iterate over each character and convert to lowercase
    for (char& c : res) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    res[0] = std::toupper(static_cast<unsigned char>(res[0]));
    return res;
}
