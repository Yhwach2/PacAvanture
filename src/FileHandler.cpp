#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <pwd.h>
#endif

bool FileHandler::saveGame(int level, int score, int lives, int coins) {
    std::string path = "pacsave.dat";
    std::ofstream file(path, std::ios::binary);

    if (!file.is_open()) {
        return false;
    }

    file.write(reinterpret_cast<const char*>(&level), sizeof(level));
    file.write(reinterpret_cast<const char*>(&score), sizeof(score));
    file.write(reinterpret_cast<const char*>(&lives), sizeof(lives));
    file.write(reinterpret_cast<const char*>(&coins), sizeof(coins));

    file.close();
    return true;
}

bool FileHandler::loadGame(int& level, int& score, int& lives, int& coins) {
    std::string path = "pacsave.dat";
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open()) {
        return false;
    }

    file.read(reinterpret_cast<char*>(&level), sizeof(level));
    file.read(reinterpret_cast<char*>(&score), sizeof(score));
    file.read(reinterpret_cast<char*>(&lives), sizeof(lives));
    file.read(reinterpret_cast<char*>(&coins), sizeof(coins));

    file.close();
    return true;
}