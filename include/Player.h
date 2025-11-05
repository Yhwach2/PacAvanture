
#ifndef PACAVANTURE_PLAYER_H
#define PACAVANTURE_PLAYER_H
#include <utility>

/**
 * Player represents the controllable Pacman-like character.
 */
class Player {
public:
    Player();
    Player(int startX, int startY);

    // movement: dx,dy are -1/0/1; returns true if moved
    bool move(int dx, int dy, const int mapWidth, const int mapHeight);
    std::pair<int,int> getPosition() const;
    void setPosition(int x, int y);
    int getX() const;
    int getY() const;

    // coin collection
    void collectCoin();
    int getScore() const;

private:
    int x;
    int y;
    int score;
};
#endif //PACAVANTURE_PLAYER_H