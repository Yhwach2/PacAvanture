#ifndef PACAVANTURE_GAME_H
#define PACAVANTURE_GAME_H

#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Map.h"

class Game {
public:
    Game();

    void run();  // Main game loop

private:
    Map map;
    Player player;
    std::vector<Enemy> enemies;

    bool gameRunning;
    bool gameWon;
    bool gameOver;

    void processInput();
    void update();
    void render();
    void checkCollisions();
    void spawnEnemies();
};

#endif