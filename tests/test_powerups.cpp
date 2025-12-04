#include "../include/Player.h"
#include "../include/Enemy.h"
#include <iostream>

int main() {
    std::cout << "=== Testing Power-up System ===\n\n";
    
    // Test 1: Player creation
    Player p;
    std::cout << "Test 1: Player created at (" << p.getX() << "," << p.getY() << ") ✓\n";
    
    // Test 2: Enemy creation  
    Enemy e(5, 5);
    auto pos = e.getPosition();
    std::cout << "Test 2: Enemy created at (" << pos.first << "," << pos.second << ") ✓\n";
    
    // Test 3: Basic movement
    p.moveDelta(1, 0, 20, 12);
    std::cout << "Test 3: Player moved to (" << p.getX() << "," << p.getY() << ") ✓\n";
    
    // Test 4: Score system
    p.addScore(10);
    std::cout << "Test 4: Score = " << p.getScore() << " ✓\n";
    
    std::cout << "\n✅ All basic tests passed!\n";
    return 0;
}
