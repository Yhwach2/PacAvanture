#ifndef PACAVANTURE_GAME_H
#define PACAVANTURE_GAME_H
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "InputHandler.h"

/**
 * Game class coordinates the main game loop and overall state.
 */
class Game {
public:
    Game();
    ~Game();

    // Initialize and run the main loop
    void initialize();
    void run();
    void update();   // one tick update: input, movement, collisions
    void render() const;
    bool isRunning() const;

private:
    Map map;
    Player player;
    std::vector<Enemy> enemies;
    InputHandler input;

    int score;
    int remainingCoins;
    bool running;
    bool victory;
    bool gameOver;

    // Helpers
    void handleCollisions();
    void checkWinLoss();
    void spawnEnemies();
    void placeCoins();
};

#endif //PACAVANTURE_GAME_H