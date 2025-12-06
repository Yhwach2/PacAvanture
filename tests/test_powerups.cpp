#include "../include/Player.h"
#include "../include/Enemy.h"
#include <cassert>
#include <iostream>

void test_powerup_collection() {
    std::cout << "Test: Power-up collection...";
    
    Player p;
    p.collectPowerUp(Player::SPEED_BOOST);
    
    assert(p.hasPowerUp(Player::SPEED_BOOST) == true);
    assert(p.hasPowerUp(Player::INSTA_KILL) == false);
    
    std::cout << " PASSED\n";
}

void test_enemy_kill() {
    std::cout << "Test: Enemy kill mechanics...";
    
    Enemy e(5, 5);
    assert(e.isAlive() == true);
    
    e.kill();
    assert(e.isAlive() == false);
    
    std::cout << " PASSED\n";
}

void test_powerup_timers() {
    std::cout << "Test: Power-up timers...";
    
    Player p;
    p.collectPowerUp(Player::GHOST_MODE);
    
    // Should have timer > 0
    assert(p.getPowerUpTimer(Player::GHOST_MODE) > 0);
    
    std::cout << " PASSED\n";
}

int main() {
    std::cout << "=== Testing Power-up System ===\n\n";
    
    test_powerup_collection();
    test_enemy_kill();
    test_powerup_timers();
    
    std::cout << "\n✅ All power-up tests passed!\n";
    return 0;
}
/*
*belluciwz@Bellucis-MacBook-Pro build % ./PacAVanture

=== PACAVANTURE ===

CHECKPOINT 2 SUBMISSION

FEATURES IMPLEMENTED:
====================
1. Map Class ✓
   - 20x12 grid with walls
   - Coin placement system
   - Gate locking mechanism

2. Player Class ✓
   - Position tracking (x, y)
   - WASD movement system
   - Score accumulation
   - Power-up collection

3. Enemy Class ✓
   - Patrol pattern AI
   - Position management
   - Collision detection

4. Power-up System ✓
   - Speed Boost (temporary)
   - Insta-Kill (destroy enemies)
   - Ghost Mode (wall phasing)

5. Game Class ✓
   - Main game loop
   - Input handling
   - Win/Lose conditions

BUILD STATUS: SUCCESSFUL
All classes compile and link correctly.
 */