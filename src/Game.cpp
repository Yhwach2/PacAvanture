#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <limits>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

Game::Game() : gameRunning(true), gameWon(false), gameOver(false),
               currentLevel(1), totalLevels(3), playerLives(3) {
    srand(time(0));
}

void Game::run() {
    showMainMenu();
}

void Game::showMainMenu() {
    while (true) {
        clearScreen();
        std::cout << "=== PACAVANTURE ===\n\n";
        std::cout << "1. New Game\n";
        std::cout << "2. Load Game\n";
        std::cout << "3. How to Play\n";
        std::cout << "4. Exit\n\n";
        std::cout << "Select: ";

        char choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case '1':
                startNewGame();
                return;
            case '2':
                if (loadSavedGame()) {
                    playGame();
                    return;
                }
                break;
            case '3':
                showInstructions();
                break;
            case '4':
                return;
            default:
                std::cout << "Invalid choice!\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                break;
        }
    }
}

void Game::showInstructions() {
    clearScreen();
    std::cout << "=== HOW TO PLAY ===\n\n";
    std::cout << "WASD: Move\n";
    std::cout << "P: Save game\n";
    std::cout << "Q: Quit to menu\n";
    std::cout << "\nGoal: Collect all coins (o)\n";
    std::cout << "Avoid enemies (E) or kill them with K power-up\n";
    std::cout << "Power-ups: S=Speed, K=Kill, G=Ghost\n";
    std::cout << "Reach the open gate (g) after collecting all coins\n";
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void Game::startNewGame() {
    resetGame();
    loadLevel(1);
    playGame();
}

void Game::playGame() {
    gameRunning = true;
    gameWon = false;
    gameOver = false;

    while (gameRunning) {
        processInput();
        update();
        render();
        checkCollisions();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        clearScreen();
    }

    // Game ended, show result
    clearScreen();
    if (gameWon) {
        std::cout << "\n🎉 YOU WIN! 🎉\n";
        std::cout << "Final Score: " << player.getScore() << "\n";
    } else if (gameOver) {
        std::cout << "\n💀 GAME OVER! 💀\n";
        std::cout << "Final Score: " << player.getScore() << "\n";
    }

    std::cout << "\nPress Enter to return to menu...";
    std::cin.ignore();
    std::cin.get();
}

bool Game::loadSavedGame() {
    clearScreen();
    std::cout << "Loading game...\n";

    int savedLevel, savedScore, savedLives, savedCoins;
    if (FileHandler::loadGame(savedLevel, savedScore, savedLives, savedCoins)) {
        currentLevel = savedLevel;
        playerLives = savedLives;
        player.addScore(savedScore);
        loadLevel(currentLevel);
        std::cout << "Game loaded! Level " << currentLevel << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return true;
    } else {
        std::cout << "No save file found!\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return false;
    }
}

void Game::loadLevel(int level) {
    currentLevel = level;
    int width = 20 + (level - 1) * 2;
    int height = 12 + (level - 1);

    map = Map(width, height);
    map.loadLevelDesign(level);
    player.setPosition(1, 1);

    enemies.clear();
    int enemyCount = 2 + level;
    for (int i = 0; i < enemyCount; i++) {
        enemies.push_back(Enemy(5 + rand() % (width - 10), 3 + rand() % (height - 6)));
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
                case 'p': case 'P': saveGame(); break;
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
    int bytes = read(STDIN_FILENO, &ch, 1);

    if (bytes > 0) {
        switch (ch) {
            case 'w': case 'W': player.moveDelta(0, -1, map.getWidth(), map.getHeight()); break;
            case 's': case 'S': player.moveDelta(0, 1, map.getWidth(), map.getHeight()); break;
            case 'a': case 'A': player.moveDelta(-1, 0, map.getWidth(), map.getHeight()); break;
            case 'd': case 'D': player.moveDelta(1, 0, map.getWidth(), map.getHeight()); break;
            case 'q': case 'Q': gameRunning = false; break;
            case 'p': case 'P': saveGame(); break;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
}

void Game::saveGame() {
    if (FileHandler::saveGame(currentLevel, player.getScore(), playerLives, map.remainingCoins())) {
        std::cout << "\nGame saved!\n";
    } else {
        std::cout << "\nSave failed!\n";
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
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
        if (currentLevel < totalLevels) {
            currentLevel++;
            player.addScore(100);
            std::cout << "\nLevel complete! Next level...\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            loadLevel(currentLevel);
        } else {
            gameWon = true;
            gameRunning = false;
        }
    }
}

void Game::render() {
    map.draw(player);

    std::cout << "\nLevel: " << currentLevel << "/" << totalLevels;
    std::cout << " | Lives: " << playerLives;
    std::cout << " | Score: " << player.getScore();
    std::cout << " | Coins: " << map.remainingCoins() << "\n";

    if (player.hasPowerUp(Player::SPEED_BOOST)) std::cout << "[SPEED] ";
    if (player.hasPowerUp(Player::INSTA_KILL)) std::cout << "[KILL] ";
    if (player.hasPowerUp(Player::GHOST_MODE)) std::cout << "[GHOST] ";

    std::cout << "\nWASD=Move | Q=Quit | P=Save\n";
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

        auto pos = enemy.getPosition();
        if (pos.first == px && pos.second == py) {
            if (player.canKillEnemies()) {
                enemy.kill();
                player.addScore(50);
            } else {
                playerLives--;
                if (playerLives <= 0) {
                    gameOver = true;
                    gameRunning = false;
                } else {
                    std::cout << "\nHit! Lives left: " << playerLives << "\n";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    loadLevel(currentLevel);
                }
                return;
            }
        }
    }
}