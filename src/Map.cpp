#include "Map.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

Map::Map(int w, int h)
    : width(w), height(h), coinCount(0), gate_is_locked(true) {
    srand(time(0));
    grid.resize(height, std::string(width, '.'));
}

Map::~Map() {}

int Map::getWidth() const { return width; }
int Map::getHeight() const { return height; }

void Map::initialize() {
    // Borders
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
                grid[y][x] = '#';
            else
                grid[y][x] = '.';
        }
    }

    // Random coins
    coinCount = 0;
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            if (rand() % 10 == 0) {
                grid[y][x] = 'o';
                coinCount++;
            }
        }
    }

    // Gate location
    gateX = width - 2;
    gateY = height / 2;
    grid[gateY][gateX] = 'G';
    gate_is_locked = true;

    // Clear any old power-ups
    powerUpPositions.clear();
    powerUpTypes.clear();

    // Spawn initial power-ups
    for (int i = 0; i < 3; i++) {
        spawnPowerUp();
    }
}

void Map::loadLevelDesign(int level) {
    // Reset grid
    grid.clear();
    grid.resize(height, std::string(width, '.'));

    // Always have borders
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
                grid[y][x] = '#';
        }
    }

    // Level-specific designs
    switch (level) {
        case 1:  // Easy - open space
            // Add some interior walls
            for (int x = 5; x < 15; x++) {
                grid[5][x] = '#';
                grid[7][x] = '#';
            }
            break;

        case 2:  // Medium - more maze-like
            for (int x = 3; x < width - 3; x += 2) {
                grid[3][x] = '#';
                grid[height - 4][x] = '#';
            }
            // Vertical walls
            for (int y = 2; y < height - 2; y++) {
                grid[y][8] = '#';
                grid[y][12] = '#';
            }
            break;

        case 3:  // Hard - complex maze
            // Create maze pattern
            for (int y = 2; y < height - 2; y += 2) {
                for (int x = 2; x < width - 2; x++) {
                    grid[y][x] = '#';
                }
            }
            // Open some paths
            for (int y = 2; y < height - 2; y += 4) {
                grid[y][5] = '.';
                grid[y][10] = '.';
                grid[y][15] = '.';
            }
            break;
    }

    // Add coins (fewer in harder levels)
    coinCount = 0;
    int coinsToAdd = 15 - (level * 3);  // Level 1: 12 coins, Level 2: 9, Level 3: 6

    for (int i = 0; i < coinsToAdd; i++) {
        int x = 1 + rand() % (width - 2);
        int y = 1 + rand() % (height - 2);

        if (grid[y][x] == '.') {
            grid[y][x] = 'o';
            coinCount++;
        }
    }

    // Gate location (always right side middle)
    gateX = width - 2;
    gateY = height / 2;
    if (gateX < width && gateY < height) {
        grid[gateY][gateX] = 'G';
    }
    gate_is_locked = true;

    // Clear power-ups for fresh level
    powerUpPositions.clear();
    powerUpTypes.clear();

    // Add initial power-ups (fewer in higher levels)
    int powerUps = 4 - level;  // Level 1: 3, Level 2: 2, Level 3: 1
    for (int i = 0; i < powerUps; i++) {
        spawnPowerUp();
    }
}

void Map::placePlayer(Player &player) {
    player.setPosition(1, 1);
}

bool Map::isInside(int x, int y) const {
    return x >= 0 && y >= 0 && x < width && y < height;
}

bool Map::isWall(int x, int y) const {
    if (!isInside(x, y)) return true;
    return grid[y][x] == '#';
}

bool Map::isValidMove(int x, int y) const {
    if (!isInside(x, y)) return false;
    return grid[y][x] != '#';
}

void Map::draw(const Player &player) const {
    // Create a copy to draw on
    std::vector<std::string> display = grid;

    // Draw power-ups
    for (size_t i = 0; i < powerUpPositions.size(); i++) {
        int px = powerUpPositions[i].first;
        int py = powerUpPositions[i].second;
        if (isInside(px, py)) {
            display[py][px] = powerUpTypes[i]; // S, K, or G
        }
    }

    // Draw player
    int px = player.getX();
    int py = player.getY();
    if (isInside(px, py)) {
        display[py][px] = 'P';
    }

    // Draw gate (open/closed)
    if (isInside(gateX, gateY)) {
        display[gateY][gateX] = gate_is_locked ? 'D' : ' ';
    }

    // Clear screen and draw with box border
    std::cout << "\n";
    std::cout << "+";
    for (int x = 0; x < width; x++) std::cout << "--";
    std::cout << "+\n";

    for (int y = 0; y < height; y++) {
        std::cout << "|";
        for (int x = 0; x < width; x++) {
            char c = display[y][x];
            if (c == '#') std::cout << "##";      // Wall
            else if (c == 'o') std::cout << " *"; // Coin
            else if (c == 'P') std::cout << " P"; // Player (you)
            else if (c == 'S') std::cout << " S"; // Speed power-up
            else if (c == 'K') std::cout << " K"; // Kill power-up
            else if (c == 'G') std::cout << " G"; // Ghost power-up
            else if (c == 'D') std::cout << " D"; // Door (locked)
            else std::cout << "  ";               // Empty space
        }
        std::cout << "|\n";
    }

    std::cout << "+";
    for (int x = 0; x < width; x++) std::cout << "--";
    std::cout << "+\n";

    // Legend
    std::cout << "\nLEGEND:  P = You   * = Coin   D = Door\n";
    std::cout << "        S = Speed  K = Kill   G = Ghost\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Score: " << player.getScore() << "  |  Coins left: " << coinCount << "\n";
}

bool Map::hasCoinAt(int x, int y) const {
    return isInside(x, y) && grid[y][x] == 'o';
}

void Map::collectCoinAt(int x, int y) {
    if (hasCoinAt(x, y)) {
        grid[y][x] = '.';
        coinCount--;

        // Sometimes spawn power-up when coin collected
        if (rand() % 5 == 0) {
            spawnPowerUp();
        }
    }
}

int Map::remainingCoins() const {
    return coinCount;
}

int Map::totalCoins() const {
    return coinCount;
}

void Map::setGateLocked(bool locked) {
    gate_is_locked = locked;
}

bool Map::gateLocked() const {
    return gate_is_locked;
}

void Map::spawnPowerUp() {
    // Find empty spot
    int tries = 0;
    while (tries < 50) {
        int x = 1 + rand() % (width - 2);
        int y = 1 + rand() % (height - 2);

        if (grid[y][x] == '.' && !hasPowerUpAt(x, y)) {
            powerUpPositions.push_back({x, y});

            // Random type
            int type = rand() % 3;
            if (type == 0) powerUpTypes.push_back('S');
            else if (type == 1) powerUpTypes.push_back('K');
            else powerUpTypes.push_back('G');

            return;
        }
        tries++;
    }
}

bool Map::hasPowerUpAt(int x, int y) const {
    for (const auto& pos : powerUpPositions) {
        if (pos.first == x && pos.second == y) {
            return true;
        }
    }
    return false;
}

char Map::getPowerUpAt(int x, int y) const {
    for (size_t i = 0; i < powerUpPositions.size(); i++) {
        if (powerUpPositions[i].first == x && powerUpPositions[i].second == y) {
            return powerUpTypes[i];
        }
    }
    return ' ';
}

void Map::collectPowerUpAt(int x, int y) {
    for (size_t i = 0; i < powerUpPositions.size(); i++) {
        if (powerUpPositions[i].first == x && powerUpPositions[i].second == y) {
            powerUpPositions.erase(powerUpPositions.begin() + i);
            powerUpTypes.erase(powerUpTypes.begin() + i);
            return;
        }
    }
}