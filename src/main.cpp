#include "../include/Map.h"
#include "../include/Player.h"
#include <iostream>

int main() {
    Map map(20, 12);
    Player player;

    map.initialize();
    map.placePlayer(player);

    map.draw(player);

    return 0;
}
