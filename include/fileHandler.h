#ifndef PACAVANTURE_FILEHANDLER_H
#define PACAVANTURE_FILEHANDLER_H

#include <string>

class FileHandler {
public:
    static bool saveGame(int level, int score, int lives, int coins);
    static bool loadGame(int& level, int& score, int& lives, int& coins);
};

#endif