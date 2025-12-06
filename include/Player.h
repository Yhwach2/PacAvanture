#ifndef PACAVANTURE_PLAYER_H
#define PACAVANTURE_PLAYER_H

class Player {
public:
    Player();
    Player(int x_, int y_);

    int getX() const;
    int getY() const;
    void setPosition(int nx, int ny);

    bool moveDelta(int dx, int dy, int mapW, int mapH);

    int getScore() const;
    void addScore(int v);

    // New power-up stuff
    enum PowerUp {
        NONE = 0,
        SPEED_BOOST = 1,
        INSTA_KILL = 2,
        GHOST_MODE = 3
    };

    void collectPowerUp(PowerUp type);
    void updatePowerUps();  // Called each game tick
    bool hasPowerUp(PowerUp type) const;
    int getPowerUpTimer(PowerUp type) const;

    bool canKillEnemies() const;
    bool canPassWalls() const;
    bool hasSpeedBoost() const;

private:
    int x, y;
    int score;

    // Power-up timers (in game ticks)
    int speedTimer;
    int killTimer;
    int ghostTimer;
};

#endif