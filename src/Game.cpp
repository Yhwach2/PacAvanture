#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

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
        std::cout << "2. Load Game\n";
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
                gameRunning = true;
                break;
            case '2':
                showLoadMenu();
                break;
            case '3':
                clearScreen();
                std::cout << "=== HOW TO PLAY ===\n\n";
                std::cout << "Controls: WASD or Arrow Keys\n";
                std::cout << "Save Game: Press 'S' during play\n";
                std::cout << "Goal: Collect coins, avoid enemies\n";
                std::cout << "Power-ups: S=Speed, K=Kill, G=Ghost\n";
                std::cout << "Lives: " << playerLives << " | Levels: " << totalLevels << "\n";
                std::cout << "\nPress any key...";
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

void Game::showSaveMenu() {
    clearScreen();
    std::cout << "=== SAVE GAME ===\n\n";

    if (saveCurrentGame()) {
        std::cout << "Game saved to pacsave.dat\n";
    } else {
        std::cout << "Save failed!\n";
    }

    std::cout << "\nPress any key to continue...";
    #ifdef _WIN32
    _getch();
    #else
    system("read -n 1");
    #endif
}

void Game::showLoadMenu() {
    clearScreen();
    std::cout << "=== LOAD GAME ===\n\n";

    if (loadSavedGame()) {
        std::cout << "Game loaded! Starting level " << currentLevel << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        inMenu = false;
        gameRunning = true;
    } else {
        std::cout << "No save file found!\n";
        std::cout << "\nPress any key to continue...";
        #ifdef _WIN32
        _getch();
        #else
        system("read -n 1");
        #endif
    }
}

bool Game::saveCurrentGame() {
    return FileHandler::saveGame(currentLevel, player.getScore(), playerLives, map.remainingCoins());
}

bool Game::loadSavedGame() {
    int savedLevel, savedScore, savedLives, savedCoins;

    if (FileHandler::loadGame(savedLevel, savedScore, savedLives, savedCoins)) {
        currentLevel = savedLevel;
        playerLives = savedLives;
        player.addScore(savedScore);

        // Load the level
        loadLevel(currentLevel);
        return true;
    }
    return false;
}

void Game::loadLevel(int level) {
    currentLevel = level;

    int width = 20 + (level - 1) * 2;
    int height = 12 + (level - 1);

    map = Map(width, height);
    map.initialize();

    player.setPosition(1, 1);

    enemies.clear();
    int enemyCount = 2 + level;

    for (int i = 0; i < enemyCount; i++) {
        int ex = 5 + rand() % (width - 10);
        int ey = 3 + rand() % (height - 6);
        enemies.push_back(Enemy(ex, ey));
    }
}

void Game::nextLevel() {
    if (currentLevel < totalLevels) {
        currentLevel++;
        player.addScore(100);
        loadLevel(currentLevel);
    } else {
        gameWon = true;
        gameRunning = false;
        player.addScore(500);
    }
}

void Game::resetGame() {
    player = Player();
    playerLives = 3;
    currentLevel = 1;
    gameWon = false;
    gameOver = false;
}

void Game::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Game::run() {
    if (inMenu) showMenu();

    while (gameRunning) {
        processInput();
        update();
        render();
        checkCollisions();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        clearScreen();
    }

    if (gameWon) {
        std::cout << "\n🎉 YOU WIN! Score: " << player.getScore() << " 🎉\n";
    } else if (gameOver) {
        std::cout << "\n💀 GAME OVER! Score: " << player.getScore() << " 💀\n";
    }
}

void Game::processInput() {
#ifdef _WIN32
    if (_kbhit()) {
        char ch = _getch();
        if (ch == 0 || ch == 224) {
            ch = _getch();
            switch (ch) {
                case 72: player.moveDelta(0, -1, map.getWidth(), map.getHeight()); break;
                case 80: player.moveDelta(0, 1, map.getWidth(), map.getHeight()); break;
                case 75: player.moveDelta(-1, 0, map.getWidth(), map.getHeight()); break;
                case 77: player.moveDelta(1, 0, map.getWidth(), map.getHeight()); break;
            }
        } else {
            switch (ch) {
                case 'w': case 'W': player.moveDelta(0, -1, map.getWidth(), map.getHeight()); break;
                case 's': case 'S': player.moveDelta(0, 1, map.getWidth(), map.getHeight()); break;
                case 'a': case 'A': player.moveDelta(-1, 0, map.getWidth(), map.getHeight()); break;
                case 'd': case 'D': player.moveDelta(1, 0, map.getWidth(), map.getHeight()); break;
                case 'q': case 'Q': gameRunning = false; break;
                case 's': case 'S': showSaveMenu(); break;
            }
        }
    }
#else
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
            case 's': case 'S': showSaveMenu(); break;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
}

void Game::update() {
    player.updatePowerUps();

    for (auto& enemy : enemies) {
        enemy.update();
    }

    if (map.remainingCoins() == 0) {
        map.setGateLocked(false);
    }

    if (!map.gateLocked() &&
        player.getX() == map.getWidth() - 2 &&
        player.getY() == map.getHeight() / 2) {
        nextLevel();
    }
}

void Game::render() {
    map.draw(player);

    std::cout << "Level: " << currentLevel << " | ";
    std::cout << "Lives: " << playerLives << " | ";
    std::cout << "Score: " << player.getScore() << "\n";
    std::cout << "Coins: " << map.remainingCoins() << " | ";
    std::cout << "Enemies: " << enemies.size() << "\n";

    if (player.hasPowerUp(Player::SPEED_BOOST)) std::cout << "SPEED ";
    if (player.hasPowerUp(Player::INSTA_KILL)) std::cout << "KILL ";
    if (player.hasPowerUp(Player::GHOST_MODE)) std::cout << "GHOST ";

    std::cout << "\nWASD=Move | Q=Quit | S=Save\n";
}

void Game::checkCollisions() {
    int px = player.getX();
    int py = player.getY();

    if (map.hasCoinAt(px, py)) {
        map.collectCoinAt(px, py);
        player.addScore(10);
    }

    if (map.hasPowerUpAt(px, py)) {
        char ptype = map.getPowerUpAt(px, py);
        map.collectPowerUpAt(px, py);

        if (ptype == 'S') player.collectPowerUp(Player::SPEED_BOOST);
        else if (ptype == 'K') player.collectPowerUp(Player::INSTA_KILL);
        else if (ptype == 'G') player.collectPowerUp(Player::GHOST_MODE);
    }

    for (auto& enemy : enemies) {
        if (!enemy.isAlive()) continue;

        auto epos = enemy.getPosition();
        if (epos.first == px && epos.second == py) {
            if (player.canKillEnemies()) {
                enemy.kill();
                player.addScore(50);
            } else {
                playerLives--;
                if (playerLives <= 0) {
                    gameOver = true;
                    gameRunning = false;
                } else {
                    loadLevel(currentLevel);
                }
                return;
            }
        }
    }
}

void Game::spawnEnemies() {
    // Handled in loadLevel
}