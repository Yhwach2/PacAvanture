#include "Enemy.h"
#include <cstdlib>
#include <ctime>

Enemy::Enemy() : x(0), y(0), alive(true), moveCounter(0), moveDirection(0) {
    moveDirection = rand() % 4;
}

Enemy::Enemy(int startX, int startY)
    : x(startX), y(startY), alive(true), moveCounter(0), moveDirection(rand() % 4) {
}

std::pair<int, int> Enemy::getPosition() const {
    return {x, y};
}

void Enemy::setPosition(int nx, int ny) {
    x = nx;
    y = ny;
}

bool Enemy::isAlive() const {
    return alive;
}

void Enemy::kill() {
    alive = false;
}

void Enemy::update() {
    if (!alive) return;

    moveCounter++;
    if (moveCounter < 3) return;

    moveCounter = 0;

    // 25% chance to change direction
    if (rand() % 4 == 0) {
        moveDirection = rand() % 4;
    }

    int oldX = x, oldY = y;

    switch (moveDirection) {
        case 0: y--; break; // up
        case 1: x++; break; // right
        case 2: y++; break; // down
        case 3: x--; break; // left
    }

    // Simple boundary check - in real game would use Map::isWall
    // Using approximate bounds
    if (x < 1 || y < 1) {
        x = oldX;
        y = oldY;
        moveDirection = (moveDirection + 2) % 4;
    }
}