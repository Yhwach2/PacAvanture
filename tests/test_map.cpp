#include "../include/Map.h"
#include <cassert>
#include <iostream>

void test_initial_state() {
    Map m(20, 12);
    assert(m.getWidth() == 20);
    assert(m.getHeight() == 12);
    std::cout << "✓ initial state\n";
}

void test_basic_functionality() {
    Map m(10, 10);
    
    // Just test it exists and has basic methods
    assert(m.getWidth() == 10);
    assert(m.getHeight() == 10);
    
    // Test wall detection at edges
    assert(m.isWall(0, 0) == true);  // Should be wall at border
    assert(m.isWall(5, 5) == false); // Should be open inside (once initialized)
    
    std::cout << "✓ basic functionality\n";
}

void test_player_placement() {
    Map m(15, 10);
    Player p;
    
    // Test we can place player
    m.placePlayer(p);
    
    // Player should be at valid position
    assert(p.getX() >= 0);
    assert(p.getY() >= 0);
    assert(p.getX() < m.getWidth());
    assert(p.getY() < m.getHeight());
    
    std::cout << "✓ player placement\n";
}

int main() {
    std::cout << "=== Running Map Tests ===\n\n";
    
    test_initial_state();
    test_basic_functionality();
    test_player_placement();
    
    std::cout << "\n✅ All map tests passed!\n";
    return 0;
}
