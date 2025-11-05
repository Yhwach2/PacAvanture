#ifndef PACAVANTURE_MAP_H
#define PACAVANTURE_MAP_H

#include <vector>
#include <string>

/**
 * Map stores grid layout: walls, empty space, coins, gate.
 * It provides rendering and basic queries (isWall, hasCoin, removeCoin).
 */
class Map {
public:
    Map();
    Map(int width, int height);

    int getWidth() const;
    int getHeight() const;

    // Rendering: returns a vector<string> where each string is a row
    std::vector<std::string> render(int playerX, int playerY,
                                    const std::vector<std::pair<int,int>>& enemyPositions,
                                    bool gateOpen) const;

    bool isWall(int x, int y) const;
    bool hasCoin(int x, int y) const;
    void removeCoin(int x, int y);
    std::pair<int,int> getGatePosition() const;
    void openGate();

    // load or generate map
    void generateDefault();

    int countCoins() const;

private:
    int width;
    int height;
    std::vector<std::string> grid; // characters: '#' wall, '.' floor, 'o' coin, 'G' gate closed, 'g' gate open
    bool gateOpen;
};

#endif //PACAVANTURE_MAP_H