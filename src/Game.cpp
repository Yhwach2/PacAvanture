#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

Game::Game() : gameRunning(true), gameWon(false), gameOver(false) {
    srand(time(0));
    map.initialize();
    map.placePlayer(player);
    spawnEnemies();
}

void Game::spawnEnemies() {
    enemies.clear();

    // Spawn 3 enemies at different spots
    enemies.push_back(Enemy(5, 5));
    enemies.push_back(Enemy(10, 3));
    enemies.push_back(Enemy(15, 7));
}

void Game::run() {
    std::cout << "=== PACAVANTURE ===\n";
    std::cout << "Arrow keys to move\n";
    std::cout << "Collect coins (o), avoid enemies (E)\n";
    std::cout << "Power-ups: S=Speed, K=Kill, G=Ghost\n";
    std::cout << "Collect all coins to open gate (G/g)\n";
    std::cout << "Press any key to start...\n";

    // Wait for key (simple way)
    #ifdef _WIN32
    _getch();
    #else
    system("read -n 1");
    #endif

    while (gameRunning) {
        processInput();
        update();
        render();
        checkCollisions();

        // Small delay so game isn't too fast
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Clear screen for next frame (simple way)
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
    }

    if (gameWon) {
        std::cout << "\n🎉 YOU WIN! Score: " << player.getScore() << " 🎉\n";
    } else if (gameOver) {
        std::cout << "\n💀 GAME OVER! Score: " << player.getScore() << " 💀\n";
    }
}

void Game::processInput() {
    // Simple input for now - we can improve later
    #ifdef _WIN32
    if (_kbhit()) {
        char ch = _getch();
        if (ch == 0 || ch == 224) {  // Arrow keys on Windows
            ch = _getch();
            switch (ch) {
                case 72: player.moveDelta(0, -1, map.getWidth(), map.getHeight()); break; // up
                case 80: player.moveDelta(0, 1, map.getWidth(), map.getHeight()); break;  // down
                case 75: player.moveDelta(-1, 0, map.getWidth(), map.getHeight()); break; // left
                case 77: player.moveDelta(1, 0, map.getWidth(), map.getHeight()); break;  // right
            }
        } else {
            // WASD as fallback
            switch (ch) {
                case 'w': case 'W': player.moveDelta(0, -1, map.getWidth(), map.getHeight()); break;
                case 's': case 'S': player.moveDelta(0, 1, map.getWidth(), map.getHeight()); break;
                case 'a': case 'A': player.moveDelta(-1, 0, map.getWidth(), map.getHeight()); break;
                case 'd': case 'D': player.moveDelta(1, 0, map.getWidth(), map.getHeight()); break;
                case 'q': case 'Q': gameRunning = false; break;
            }
        }
    }
    #else
    // Linux/Mac simple input (non-blocking attempt)
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char ch = 0;
    if (read(STDIN_FILENO, &ch, 1) > 0) {
        switch (ch) {
            case 'w': case 'W': player.moveDelta(0, -1, map.getWidth(), map.getHeight()); break;
            case 's': case 'S': player.moveDelta(0, 1, map.getWidth(), map.getHeight()); break;
            case 'a': case 'A': player.moveDelta(-1, 0, map.getWidth(), map.getHeight()); break;
            case 'd': case 'D': player.moveDelta(1, 0, map.getWidth(), map.getHeight()); break;
            case 'q': case 'Q': gameRunning = false; break;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    #endif
}

void Game::update() {
    // Update player power-up timers
    player.updatePowerUps();

    // Update enemies
    for (auto& enemy : enemies) {
        enemy.update();
    }

    // Check if all coins collected
    if (map.remainingCoins() == 0) {
        map.setGateLocked(false);
    }

    // Check if player at open gate
    if (!map.gateLocked() &&
        player.getX() == map.getWidth() - 2 &&
        player.getY() == map.getHeight() / 2) {
        gameWon = true;
        gameRunning = false;
    }
}

void Game::render() {
    map.draw(player);

    // Show enemy positions
    std::cout << "Enemies: ";
    for (const auto& enemy : enemies) {
        if (enemy.isAlive()) {
            auto pos = enemy.getPosition();
            std::cout << "E(" << pos.first << "," << pos.second << ") ";
        }
    }
    std::cout << "\n";

    // Instructions
    std::cout << "WASD to move | Q to quit\n";
}

void Game::checkCollisions() {
    int px = player.getX();
    int py = player.getY();

    // Check coins
    if (map.hasCoinAt(px, py)) {
        map.collectCoinAt(px, py);
        player.addScore(10);
        std::cout << "+10 points!\n";
    }

    // Check power-ups
    if (map.hasPowerUpAt(px, py)) {
        char ptype = map.getPowerUpAt(px, py);
        map.collectPowerUpAt(px, py);

        if (ptype == 'S') player.collectPowerUp(Player::SPEED_BOOST);
        else if (ptype == 'K') player.collectPowerUp(Player::INSTA_KILL);
        else if (ptype == 'G') player.collectPowerUp(Player::GHOST_MODE);
    }

    // Check enemy collisions
    for (auto& enemy : enemies) {
        if (!enemy.isAlive()) continue;

        auto epos = enemy.getPosition();
        if (epos.first == px && epos.second == py) {
            if (player.canKillEnemies()) {
                // Player kills enemy
                enemy.kill();
                player.addScore(50);
                std::cout << "Enemy destroyed! +50 points!\n";
            } else {
                // Enemy kills player
                gameOver = true;
                gameRunning = false;
                return;
            }
        }
    }
}