# Checkpoint 1 Reflection

## What I Implemented
I successfully implemented three interconnected features as a foundation for PacAvanture:

1. **Complete Map Rendering System**
    - Created a `Map` class that generates bordered grids with random coin placement
    - Implemented a gate system that starts locked ('G') and can be opened ('g')
    - Added proper wall collision detection

2. **Player Movement & Coin Collection**
    - Built a `Player` class with position tracking and scoring
    - Implemented coin collection logic: when player moves onto a coin, it's collected and score increases
    - Added boundary checking for valid movement

3. **Automated Testing Framework**
    - Created comprehensive unit tests using CTest
    - Tests verify map initialization, dimensions, and coin logic
    - All tests pass successfully with `ctest --verbose`

## Challenges I Faced
1. **Cross-platform input handling**: I initially planned to use arrow keys but encountered terminal-specific issues. I simplified to basic movement functions first, leaving platform-specific input for later.
2. **Random coin placement for testing**: I needed consistent test results, so I considered using a fixed seed for RNG during tests.
3. **Build system integration**: Getting CMake to properly link all source files and tests required careful configuration.

## What I Learned
1. **CTest framework**: Learned how to create and run automated tests with CMake's testing framework
2. **Separation of concerns**: Kept map logic, player logic, and game logic in separate classes
3. **Const-correctness**: Proper use of `const` member functions for getters
4. **Initialization lists**: Used constructor initialization lists for cleaner object creation

## Testing Results
All three test cases pass:
-  **Test 1: Initial State** - Map dimensions are correctly set
-  **Test 2: Initialize** - Map creates coins and locked gate properly
-  **Test 3: Coin Logic** - Coins can be found, collected, and count updates correctly

CTest output shows 100% pass rate with all tests completing successfully.

## Questions for Next Checkpoint
1. Should I implement platform-specific input handling now (conio.h for Windows, termios for Linux) or keep it simple with WASD?
2. How complex should enemy AI be? Should they follow simple patrol patterns or have more advanced behavior?
3. Should I add visual feedback when coins are collected (like a brief animation or message)?

## Time Spent
Approximately 5 hours:
- 2 hours: Map and Player class implementation
- 1.5 hours: Testing framework setup
- 1 hour: Documentation and build system configuration
- 0.5 hours: Debugging and polishing

## Next Steps
1. **Immediate**: Implement the Game class to tie everything together
2. **Short-term**: Add Enemy class with basic patrol patterns
3. **Medium-term**: Implement InputHandler for proper keyboard input
4. **Long-term**: Add game states (menu, playing, game over, victory)