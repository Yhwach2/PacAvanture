#ifndef PACAVANTURE_MAP_H
#define PACAVANTURE_MAP_H

#include <vector>
#include <string>
#include <utility>

class Player;  // Forward declaration

class Map {
public:
    Map(int width = 20, int height = 12);
    ~Map();

    int getWidth() const;
    int getHeight() const;

    void initialize();
    void placePlayer(Player &player);
    void draw(const Player &player) const;

    bool isInside(int x, int y) const;
    bool isWall(int x, int y) const;

    // Coin logic
    int totalCoins() const;
    bool hasCoinAt(int x, int y) const;
    void collectCoinAt(int x, int y);
    int remainingCoins() const;

    // Gate logic
    void setGateLocked(bool locked);
    bool gateLocked() const;

    // New: Power-up spawns
    void spawnPowerUp();
    bool hasPowerUpAt(int x, int y) const;
    char getPowerUpAt(int x, int y) const;  // Returns 'S', 'K', 'G' or ' '
    void collectPowerUpAt(int x, int y);

    // For enemy movement
    bool isValidMove(int x, int y) const;

private:
    int width;
    int height;
    std::vector<std::string> grid;

    int coinCount;
    int gateX, gateY;
    bool gate_is_locked;

    // Track power-up positions and types
    std::vector<std::pair<int, int>> powerUpPositions;
    std::vector<char> powerUpTypes;  // 'S'peed, 'K'ill, 'G'host
};

#endif