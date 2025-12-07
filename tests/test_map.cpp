#include "../include/Map.h"
#include <cassert>
#include <iostream>

void test_initial_state() {
    Map m(20, 12);
    assert(m.getWidth() == 20);
    assert(m.getHeight() == 12);
    std::cout << "✓ initial state\n";
}

void test_initialize() {
    Map m(20, 12);
    m.initialize();
    assert(m.totalCoins() >= 0);
    assert(m.gateLocked() == true);
    std::cout << "✓ initialize\n";
}

void test_coin_logic() {
    Map m(10, 10);
    m.initialize();

    int before = m.remainingCoins();

    // Scan for a coin
    bool found = false;
    int cx = -1, cy = -1;
    for (int y = 1; y < 9 && !found; y++) {
        for (int x = 1; x < 9 && !found; x++) {
            if (m.hasCoinAt(x, y)) {
                found = true;
                cx = x; cy = y;
            }
        }
    }

    if (found) {
        m.collectCoinAt(cx, cy);
        assert(m.remainingCoins() == before - 1);
    }

    std::cout << "✓ coin logic\n";
}

int main() {
    test_initial_state();
    test_initialize();
    test_coin_logic();

    std::cout << "All map tests passed!\n";
    return 0;
}