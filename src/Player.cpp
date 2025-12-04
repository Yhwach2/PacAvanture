#include "../include/Player.h"

Player::Player() : x(1), y(1), score(0) {}
Player::Player(int x_, int y_) : x(x_), y(y_), score(0) {}

int Player::getX() const { return x; }
int Player::getY() const { return y; }
void Player::setPosition(int nx, int ny) { x = nx; y = ny; }

bool Player::moveDelta(int dx, int dy, int mapW, int mapH) {
    int nx = x + dx;
    int ny = y + dy;
    if (nx < 0 || ny < 0 || nx >= mapW || ny >= mapH) return false;
    x = nx;
    y = ny;
    return true;
}

int Player::getScore() const { return score; }
void Player::addScore(int v) { score += v; }
