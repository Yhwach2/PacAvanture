#include "Player.h"
#include <iostream>

Player::Player() : x(1), y(1), score(0), speedTimer(0), killTimer(0), ghostTimer(0) {}

Player::Player(int x_, int y_) : x(x_), y(y_), score(0), speedTimer(0), killTimer(0), ghostTimer(0) {}

int Player::getX() const { return x; }
int Player::getY() const { return y; }
void Player::setPosition(int nx, int ny) { x = nx; y = ny; }

bool Player::moveDelta(int dx, int dy, int mapW, int mapH) {
    int nx = x + dx;
    int ny = y + dy;

    // With speed boost, sometimes move 2 spaces
    if (hasSpeedBoost() && (rand() % 3 == 0)) {
        nx = x + dx * 2;
        ny = y + dy * 2;
    }

    if (nx < 0 || ny < 0 || nx >= mapW || ny >= mapH) return false;
    x = nx;
    y = ny;
    return true;
}

int Player::getScore() const { return score; }
void Player::addScore(int v) { score += v; }

void Player::collectPowerUp(PowerUp type) {
    switch (type) {
        case SPEED_BOOST:
            speedTimer = 150;  // 5 seconds at 30 fps
            std::cout << "Speed Boost! Zoom zoom!\n";
            break;
        case INSTA_KILL:
            killTimer = 300;   // 10 seconds
            std::cout << "Insta-Kill! Enemies go brrr!\n";
            break;
        case GHOST_MODE:
            ghostTimer = 120;  // 4 seconds
            std::cout << "Ghost Mode! Walking through walls!\n";
            break;
        default:
            break;
    }
}

void Player::updatePowerUps() {
    if (speedTimer > 0) speedTimer--;
    if (killTimer > 0) killTimer--;
    if (ghostTimer > 0) ghostTimer--;

    // Notify when power-up ends
    if (speedTimer == 1) std::cout << "Speed boost wore off\n";
    if (killTimer == 1) std::cout << "No more insta-kill\n";
    if (ghostTimer == 1) std::cout << "Back to solid form\n";
}

bool Player::hasPowerUp(PowerUp type) const {
    switch (type) {
        case SPEED_BOOST: return speedTimer > 0;
        case INSTA_KILL: return killTimer > 0;
        case GHOST_MODE: return ghostTimer > 0;
        default: return false;
    }
}

int Player::getPowerUpTimer(PowerUp type) const {
    switch (type) {
        case SPEED_BOOST: return speedTimer;
        case INSTA_KILL: return killTimer;
        case GHOST_MODE: return ghostTimer;
        default: return 0;
    }
}

bool Player::canKillEnemies() const {
    return killTimer > 0;
}

bool Player::canPassWalls() const {
    return ghostTimer > 0;
}

bool Player::hasSpeedBoost() const {
    return speedTimer > 0;
}