#include "FileHandler.h"
#include <iostream>
#include <fstream>

bool FileHandler::saveGame(int level, int score, int lives, int coins) {
    std::ofstream file("pacsave.dat");
    if (!file) {
        return false;
    }

    // Simple binary-ish format
    file << level << " " << score << " " << lives << " " << coins;
    file.close();

    return true;
}

bool FileHandler::loadGame(int& level, int& score, int& lives, int& coins) {
    std::ifstream file("pacsave.dat");
    if (!file) {
        return false;
    }

    file >> level >> score >> lives >> coins;
    file.close();

    return true;
}