#ifndef PACAVANTURE_MAP_H
#define PACAVANTURE_MAP_H

#include <vector>
#include <string>
#include <utility>

class Player;

class Map {
public:
    Map(int width = 20, int height = 12);
    ~Map();

    int getWidth() const;
    int getHeight() const;

    void initialize();
    void loadLevelDesign(int level);  // ADD THIS LINE
    void placePlayer(Player &player);
    void draw(const Player &player) const;

    bool isInside(int x, int y) const;
    bool isWall(int x, int y) const;

    int totalCoins() const;
    bool hasCoinAt(int x, int y) const;
    void collectCoinAt(int x, int y);
    int remainingCoins() const;

    void setGateLocked(bool locked);
    bool gateLocked() const;

    void spawnPowerUp();
    bool hasPowerUpAt(int x, int y) const;
    char getPowerUpAt(int x, int y) const;
    void collectPowerUpAt(int x, int y);

    bool isValidMove(int x, int y) const;

private:
    int width;
    int height;
    std::vector<std::string> grid;

    int coinCount;
    int gateX, gateY;
    bool gate_is_locked;

    std::vector<std::pair<int, int>> powerUpPositions;
    std::vector<char> powerUpTypes;
};

#endif