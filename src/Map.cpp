#include "Map.h"
#include <iostream>
#include <cstdlib>

Map::Map(int w, int h)
    : width(w), height(h), coinCount(0), gate_is_locked(true) {
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
                grid[y][x] = '.'; // floor
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
    grid[gateY][gateX] = 'G'; // locked door
    gate_is_locked = true;
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

void Map::draw(const Player &player) const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (player.getX() == x && player.getY() == y)
                std::cout << 'P';
            else
                std::cout << grid[y][x];
        }
        std::cout << "\n";
    }
}

bool Map::hasCoinAt(int x, int y) const {
    return isInside(x, y) && grid[y][x] == 'o';
}

void Map::collectCoinAt(int x, int y) {
    if (hasCoinAt(x, y)) {
        grid[y][x] = '.';
        coinCount--;
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
    grid[gateY][gateX] = locked ? 'G' : 'g';
}

bool Map::gateLocked() const {
    return gate_is_locked;
}
