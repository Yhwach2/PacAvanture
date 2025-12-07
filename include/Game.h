#ifndef PACAVANTURE_GAME_H
#define PACAVANTURE_GAME_H

#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "FileHandler.h"

class Game {
public:
    Game();
    void run();  // Main entry point

private:
    Map map;
    Player player;
    std::vector<Enemy> enemies;

    bool gameRunning;
    bool gameWon;
    bool gameOver;

    int currentLevel;
    int totalLevels;
    int playerLives;

    void showMainMenu();
    void showInstructions();
    void startNewGame();
    void playGame();
    bool loadSavedGame();
    void saveGame();

    void loadLevel(int level);
    void resetGame();
    void clearScreen();

    void processInput();
    void update();
    void render();
    void checkCollisions();
};

#endif