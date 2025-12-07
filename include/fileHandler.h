#ifndef PACAVANTURE_FILEHANDLER_H
#define PACAVANTURE_FILEHANDLER_H

#include <string>
#include "Game.h"

class FileHandler {
public:
    static bool saveGame(const Game& game, const std::string& filename);
    static bool loadGame(Game& game, const std::string& filename);
    
private:
    // Helper methods
    static std::string getSavePath();
    static bool fileExists(const std::string& filename);
};

#endif