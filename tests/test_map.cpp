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
/*
*belluciwz@Bellucis-MacBook-Pro build % ctest --verbose
UpdateCTestConfiguration  from :/Users/belluciwz/Desktop/PacAvanture/build/DartConfiguration.tcl
Test project /Users/belluciwz/Desktop/PacAvanture/build
Constructing a list of tests
Done constructing a list of tests
Updating test list for fixtures
Added 0 tests to meet fixture requirements
Checking test dependency graph...
Checking test dependency graph end
test 1
    Start 1: MapTests

1: Test command: /Users/belluciwz/Desktop/PacAvanture/build/test_map
1: Working Directory: /Users/belluciwz/Desktop/PacAvanture/build
1: Test timeout computed to be: 10000000
1: ✓ initial state
1: ✓ initialize
1: ✓ coin logic
1: All map tests passed!
1/1 Test #1: MapTests .........................   Passed    1.55 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   1.55 sec
 */