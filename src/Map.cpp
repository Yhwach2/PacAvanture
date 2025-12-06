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
    return grid[y][x] != '#';  // Can move on anything but walls
}

void Map::draw(const Player &player) const {
    // Create a copy to draw on
    std::vector<std::string> display = grid;

    // Draw power-ups
    for (size_t i = 0; i < powerUpPositions.size(); i++) {
        int px = powerUpPositions[i].first;
        int py = powerUpPositions[i].second;
        if (isInside(px, py)) {
            display[py][px] = powerUpTypes[i];
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
        display[gateY][gateX] = gate_is_locked ? 'G' : 'g';
    }

    // Actually print
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << display[y][x];
        }
        std::cout << "\n";
    }

    // Show player status
    std::cout << "Score: " << player.getScore() << " | Coins left: " << coinCount;
    if (player.hasPowerUp(Player::SPEED_BOOST))
        std::cout << " | SPEED: " << player.getPowerUpTimer(Player::SPEED_BOOST)/30 << "s";
    if (player.hasPowerUp(Player::INSTA_KILL))
        std::cout << " | KILL: " << player.getPowerUpTimer(Player::INSTA_KILL)/30 << "s";
    if (player.hasPowerUp(Player::GHOST_MODE))
        std::cout << " | GHOST: " << player.getPowerUpTimer(Player::GHOST_MODE)/30 << "s";
    std::cout << "\n";
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