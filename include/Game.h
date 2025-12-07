#ifndef PACAVANTURE_GAME_H
#define PACAVANTURE_GAME_H

#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "Map.h"

class Game {
public:
    Game();

    void run();  // Main game loop
    void showMenu();  // New: Main menu

private:
    Map map;
    Player player;
    std::vector<Enemy> enemies;

    bool gameRunning;
    bool gameWon;
    bool gameOver;
    bool inMenu;

    int currentLevel;
    int totalLevels;
    int playerLives;  // New: Lives system

    void processInput();
    void update();
    void render();
    void renderMenu();
    void checkCollisions();
    void spawnEnemies();

    // New level methods
    void loadLevel(int level);
    void nextLevel();
    void resetGame();

    // New save/load (stub for now)
    bool saveGame(const std::string& filename);
    bool loadGame(const std::string& filename);

    // Helper
    void clearScreen();
};

#endif