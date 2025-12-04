#ifndef PACAVANTURE_MAP_H
#define PACAVANTURE_MAP_H

#include <vector>
#include <string>
#include "Player.h"

class Map {
public:
    Map(int width = 20, int height = 12);
    ~Map();

    // --- Public Getters ---
    int getWidth() const;
    int getHeight() const;

    // --- Map Ops ---
    void initialize();
    void placePlayer(Player &player);
    void draw(const Player &player) const;

    bool isInside(int x, int y) const;
    bool isWall(int x, int y) const;

    // --- Coin Logic ---
    int totalCoins() const;
    bool hasCoinAt(int x, int y) const;
    void collectCoinAt(int x, int y);
    int remainingCoins() const;

    // --- Gate Logic ---
    void setGateLocked(bool locked);
    bool gateLocked() const;

private:
    int width;
    int height;

    std::vector<std::string> grid;

    int coinCount;
    int gateX, gateY;
    bool gate_is_locked;
};

#endif
l