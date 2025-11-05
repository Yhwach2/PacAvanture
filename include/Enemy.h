#ifndef PACAVANTURE_ENEMY_H
#define PACAVANTURE_ENEMY_H

#include <utility>
#include <vector>

/**
 * Enemy moves in a fixed patrol pattern (sequence of dx,dy steps repeated).
 */
class Enemy {
public:
    Enemy();
    Enemy(int startX, int startY, const std::vector<std::pair<int,int>>& pattern);

    void update(); // advance one step in the patrol pattern
    std::pair<int,int> getPosition() const;
    void setPosition(int x, int y);
    bool isAt(int x, int y) const;

private:
    int x;
    int y;
    std::vector<std::pair<int,int>> pattern;
    size_t patternIndex;
};

#endif //PACAVANTURE_ENEMY_H