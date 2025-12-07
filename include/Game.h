#ifndef PACAVANTURE_GAME_H
#define PACAVANTURE_GAME_H

#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "FileHandler.h"  // ADDED

class Game {
public:
    Game();

    void run();
    void showMenu();

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
    int playerLives;

    void processInput();
    void update();
    void render();
    void renderMenu();
    void checkCollisions();
    void spawnEnemies();

    void loadLevel(int level);
    void nextLevel();
    void resetGame();
    void clearScreen();

    // Save/load using FileHandler
    void showSaveMenu();
    void showLoadMenu();
    bool saveCurrentGame();
    bool loadSavedGame();
};

#endif