#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <fstream>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

Game::Game() : gameRunning(false), gameWon(false), gameOver(false),
               inMenu(true), currentLevel(1), totalLevels(3), playerLives(3) {
    srand(time(0));
}

void Game::showMenu() {
    inMenu = true;
    while (inMenu) {
        clearScreen();

        std::cout << "=== PACAVANTURE ===\n\n";
        std::cout << "1. New Game\n";
        std::cout << "2. Load Game (coming soon)\n";
        std::cout << "3. How to Play\n";
        std::cout << "4. Exit\n\n";
        std::cout << "Select: ";

        char choice;
        std::cin >> choice;

        switch (choice) {
            case '1':
                resetGame();
                loadLevel(1);
                inMenu = false;
                run();
                break;
            case '2':
                // Will implement in next commit
                std::cout << "\nSave/Load coming in next update!\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            case '3':
                clearScreen();
                std::cout << "=== HOW TO PLAY ===\n\n";
                std::cout << "Move: WASD or Arrow Keys\n";
                std::cout << "Goal: Collect ALL coins (o)\n";
                std::cout << "Avoid enemies (E) or kill them with K power-up\n";
                std::cout << "Power-ups:\n";
                std::cout << "  S = Speed (5 sec)\n";
                std::cout << "  K = Insta-Kill (10 sec)\n";
                std::cout << "  G = Ghost (4 sec) - walk through walls!\n";
                std::cout << "\nLevels get harder with more enemies\n";
                std::cout << "You have " << playerLives << " lives\n";
                std::cout << "\nPress any key to continue...";
                #ifdef _WIN32
                _getch();
                #else
                system("read -n 1");
                #endif
                break;
            case '4':
                inMenu = false;
                gameRunning = false;
                break;
        }
    }
}

void Game::loadLevel(int level) {
    currentLevel = level;

    // Different map sizes based on level
    int width = 20 + (level - 1) * 2;  // Gets wider each level
    int height = 12 + (level - 1);     // Gets taller

    // Create new map with appropriate size
    map = Map(width, height);
    map.initialize();

    // Place player at start (different position each level)
    int startX = 1;
    int startY = 1;
    player.setPosition(startX, startY);

    // Add extra coins for higher levels
    if (level > 1) {
        // Manually add more coins
        for (int i = 0; i < level * 3; i++) {
            int x = 2 + rand() % (width - 4);
            int y = 2 + rand() % (height - 4);
            // Would need a method to add coin at position
            // For now, map.initialize() already adds random coins
        }
    }

    // Spawn more enemies for higher levels
    enemies.clear();
    int enemyCount = 2 + level;  // Level 1: 3 enemies, Level 2: 4, etc

    for (int i = 0; i < enemyCount; i++) {
        // Spread enemies out
        int ex, ey;
        do {
            ex = 5 + rand() % (width - 10);
            ey = 3 + rand() % (height - 6);
        } while (ex == startX && ey == startY);

        enemies.push_back(Enemy(ex, ey));
    }

    std::cout << "\n=== LEVEL " << level << " ===\n";
    std::cout << "Collect all " << map.remainingCoins() << " coins!\n";
    std::cout << "Avoid " << enemyCount << " enemies!\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void Game::nextLevel() {
    if (currentLevel < totalLevels) {
        currentLevel++;
        loadLevel(currentLevel);

        // Bonus points for completing level
        player.addScore(100 * (currentLevel - 1));
        std::cout << "\nLevel complete! +" << (100 * (currentLevel - 1)) << " points!\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
    } else {
        // Beat all levels
        gameWon = true;
        gameRunning = false;
        player.addScore(500);  // Final bonus
    }
}

void Game::resetGame() {
    player = Player();  // Reset player
    playerLives = 3;
    currentLevel = 1;
    gameWon = false;
    gameOver = false;
}

// Update the run() method to show menu first
void Game::run() {
    if (inMenu) {
        showMenu();
    } else {
        // Existing game loop...
    }
}

// Update checkCollisions to handle lives
void Game::checkCollisions() {
    // ... existing collision code ...

    // When player dies to enemy
    if (gameOver) {
        playerLives--;
        if (playerLives > 0) {
            std::cout << "\nYou died! " << playerLives << " lives remaining.\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));

            // Reload current level
            loadLevel(currentLevel);
            gameOver = false;
        }
    }
}