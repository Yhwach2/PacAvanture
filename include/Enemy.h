#ifndef PACAVANTURE_ENEMY_H
#define PACAVANTURE_ENEMY_H

#include <utility>
#include <vector>

class Enemy {
public:
    Enemy();
    Enemy(int startX, int startY);

    void update();  // Move the enemy
    std::pair<int, int> getPosition() const;
    void setPosition(int x, int y);

    bool isAlive() const;
    void kill();  // For when player has insta-kill power

private:
    int x, y;
    bool alive;
    int moveCounter;
    int moveDirection;  // 0=up, 1=right, 2=down, 3=left
};

#endif