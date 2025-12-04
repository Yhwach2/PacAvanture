
#ifndef PACAVANTURE_PLAYER_H
#define PACAVANTURE_PLAYER_H
class Player {
public:
    Player();
    Player(int x, int y);

    int getX() const;
    int getY() const;
    void setPosition(int x, int y);

    // attempt move, returns true if moved
    bool moveDelta(int dx, int dy, int mapW, int mapH);

    int getScore() const;
    void addScore(int v);

private:
    int x;
    int y;
    int score;
};
#endif //PACAVANTURE_PLAYER_H